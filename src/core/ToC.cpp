//
// Created by masy on 27.01.20.
//

#include "cedar/Cedar.h"
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
	cedar::initEngine(logAppender, argc, args);

	cedar::Thread *glWaitFor[1] = {EngineThread::getInstance()};
	cedar::Thread *inputWaitFor[1] = {OpenGLThread::getInstance()};
	cedar::Thread *worldWaitFor[1] = {InputThread::getInstance()};

	WorldThread::getInstance()->start(1, worldWaitFor);
	InputThread::getInstance()->start(1, inputWaitFor);
	OpenGLThread::getInstance()->start(1, glWaitFor);
	EngineThread::getInstance()->start()->join();
}

void ToC::stop()
{
	WorldThread::getInstance()->stop();
	InputThread::getInstance()->stop();
	OpenGLThread::getInstance()->stop();
	EngineThread::getInstance()->stop();
}