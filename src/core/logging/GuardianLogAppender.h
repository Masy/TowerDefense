//
// Created by masy on 01.02.20.
//

#ifndef GUARDIAN_GUARDIANLOGAPPENDER_H
#define GUARDIAN_GUARDIANLOGAPPENDER_H

#include "cedar/QueueLogAppender.hpp"
#include <fstream>

/**
 * The log appender of Guardian.
 */
class GuardianLogAppender : public cedar::QueueLogAppender
{
private:
	/**
	 * The output file stream to the log file.
	 */
	std::ofstream m_logFile;
public:
	/**
	 * Creates a new Guardian log appender.
	 */
	GuardianLogAppender();

	/**
	 * Destroys the Guardian log appender.
	 */
	~GuardianLogAppender();

	/**
	 * Starts the Guardian log appender.
	 */
	void start() override;

	/**
	 * Processes the given log event.
	 *
	 * @param logEvent A pointer to the log event that will be processed.
	 */
	void processLogEvent(const cedar::LogEvent *logEvent) override;
};

#endif //GUARDIAN_GUARDIANLOGAPPENDER_H
