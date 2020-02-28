//
// Created by masy on 01.02.20.
//

#include "ToCLogAppender.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

#ifdef WIN32
#define stat _stat
#define mkdir _mkdir
#endif

ToCLogAppender::ToCLogAppender() : QueueLogAppender()
{
	auto filename = "logs/latest.log";
	FILE *latest = fopen(filename, "r");
	if (latest)
	{
		char newName[29]; // logs/YYYY-MM-DD_HH-mm-ss.log
		struct stat result{};
		if (stat(filename, &result) == 0)
		{
			long mod_time = result.st_mtime;
			auto time = std::time(&mod_time);
			auto localTime = std::localtime(&time);
			sprintf(newName, "logs/%04d-%02d-%02d_%02d-%02d-%02d.log", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
		}

		fclose(latest);
		int rename = std::rename("logs/latest.log", newName);
	}
	else
	{
		int created = mkdir("logs", 0);
	}
}

void ToCLogAppender::start()
{
	QueueLogAppender::start();
	this->m_logFile.open("logs/latest.log", std::ios::out | std::ios::app);
	if (!this->m_logFile.is_open())
		throw cedar::LogAppenderStartException("Could not start queue log appender. Couldn't create log file!");
}

ToCLogAppender::~ToCLogAppender()
{
	this->m_logFile.close();
}

const char* intToMonth(const int month)
{
	switch (month)
	{
		case 1:
			return "JAN";

		case 2:
			return "FEB";

		case 3:
			return "MAR";

		case 4:
			return "APR";

		case 5:
			return "MAI";

		case 6:
			return "JUN";

		case 7:
			return "JUL";

		case 8:
			return "AUG";

		case 9:
			return "SEP";

		case 10:
			return "OCT";

		case 11:
			return "NOV";

		case 12:
			return "DEC";

		default:
			return "???";
	}
}

const char* levelToColor(const cedar::LogLevel &logLevel)
{
	switch (logLevel)
	{
		case cedar::INFO:
			return "\033[32m";

		case cedar::WARNING:
			return "\033[33m";

		case cedar::ERROR:
			return "\033[31m";

		case cedar::DEBUG:
			return "\033[34m";

		default:
			return "\033[0m";
	}
}

void ToCLogAppender::processLogEvent(const cedar::LogEvent *logEvent)
{
	std::stringstream fileStream;
	std::stringstream consoleStream;
	tm *localTime = std::localtime(&logEvent->m_logTime);
	char fileTimePrefix[17];
	char consoleTimePrefix[9];
	sprintf(fileTimePrefix, "[%02d %s %02d:%02d:%02d]", localTime->tm_mday, intToMonth(localTime->tm_mon + 1), localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
	sprintf(consoleTimePrefix, "%02d:%02d:%02d", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
	fileStream << fileTimePrefix << "[" << logEvent->getLogLevelAsString() << "][" << logEvent->m_loggerName << "]: " << logEvent->m_message << "\n";
	consoleStream << "\033[37m[\033[0m" << consoleTimePrefix << "\033[37m][" << levelToColor(logEvent->m_logLevel) << logEvent->getLogLevelAsString() << "\033[37m][\033[36m" << logEvent->m_loggerName << "\033[37m]\033[0m: " << logEvent->m_message << "\n";

	std::cout << consoleStream.str();
	this->m_logFile << fileStream.str();
	this->m_logFile.flush();
}
