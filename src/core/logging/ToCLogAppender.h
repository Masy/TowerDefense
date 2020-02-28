//
// Created by masy on 01.02.20.
//

#ifndef TALESOFCATVENTURE_TOCLOGAPPENDER_H
#define TALESOFCATVENTURE_TOCLOGAPPENDER_H

#include "cedar/QueueLogAppender.h"
#include <fstream>

/**
 * The log appender of ToC.
 */
class ToCLogAppender : public cedar::QueueLogAppender
{
private:
	/**
	 * The output file stream to the log file.
	 */
	std::ofstream m_logFile;
public:
	/**
	 * Creates a new ToC log appender.
	 */
	ToCLogAppender();

	/**
	 * Destroys the ToC log appender.
	 */
	~ToCLogAppender();

	/**
	 * Starts the ToC log appender.
	 */
	void start() override;

	/**
	 * Processes the given log event.
	 *
	 * @param logEvent A pointer to the log event that will be processed.
	 */
	void processLogEvent(const cedar::LogEvent *logEvent) override;
};

#endif //TALESOFCATVENTURE_TOCLOGAPPENDER_H
