//
// Created by masy on 27.01.20.
//

#include <cedar/EngineThread.h>
#include "ToC.h"
#include "ToCLogAppender.h"
#include "cedar/InputThread.h"
#include "KeyHandler.h"
#include "TerrainRenderer.h"

ToC::ToC()
{
	this->m_config = new ToCConfig();
}

ToC *ToC::getInstance()
{
	static ToC *instance = new ToC();
	return instance;
}

void ToC::preStart()
{
	config = new Config();

	ToCLogAppender *logAppender = new ToCLogAppender();
	LoggerFactory::setQueueLogAppender(logAppender);
	logAppender->start();

	cedar::EngineThread::getInstance()->setInitCallback([]() {
		EngineThread::getInstance()->setCamera(new Camera());
	});

	cedar::OpenGLThread::getInstance()->setInitCallback([](MasterRenderer *masterRenderer) {
		OpenGLThread::getInstance()->getWindow()->setTitle("ToC");
		masterRenderer->addRenderer(new TerrainRenderer());
	});

	cedar::InputThread::getInstance()->setInitCallback([](InputHandler *inputHandler) {
		KeyHandler::init(inputHandler);
	});
}

void ToC::onStart()
{
	cedar::InputThread::getInstance()->setTickCallback([](unsigned long currentTime, unsigned long tickCount, InputHandler *inputHandler) {
		KeyHandler::handle(inputHandler);
	});

	cedar::InputThread::getInstance()->setStopCallback([]() {
		KeyHandler::cleanup();
	});
}

void ToC::onStop()
{

}