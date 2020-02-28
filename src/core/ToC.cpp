//
// Created by masy on 27.01.20.
//

#include "cedar/LoggerFactory.h"
#include "ToC.h"
#include "ToCLogAppender.h"
#include "EngineThread.h"
#include "OpenGLThread.h"
#include "InputThread.h"
#include "WorldThread.h"
#include <iostream>

ToC::ToC()
{
	this->m_config = new ToCConfig();
}

ToC *ToC::getInstance()
{
	static ToC *instance = new ToC();
	return instance;
}

void ToC::start(const int argc, const char **args)
{
	ToCLogAppender *logAppender = new ToCLogAppender();
	cedar::LoggerFactory::setQueueLogAppender(logAppender);
	logAppender->start();

	cedar::Thread *waitFor[1];
	waitFor[0] = EngineThread::getInstance();
	cedar::Thread *inputWaitfor[1];
	inputWaitfor[0] = OpenGLThread::getInstance();

	WorldThread::getInstance()->start(1, waitFor);
	InputThread::getInstance()->start(1, inputWaitfor);
	OpenGLThread::getInstance()->start(1, waitFor);
	EngineThread::getInstance()->start()->join();
}

void ToC::stop()
{
	WorldThread::getInstance()->stop();
	InputThread::getInstance()->stop();
	OpenGLThread::getInstance()->stop();
	EngineThread::getInstance()->stop();
}