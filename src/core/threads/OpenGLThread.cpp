//
// Created by masy on 27.01.20.
//

#include "OpenGLThread.h"
#include "ToC.h"
#include "EngineThread.h"
#include <iostream>

OpenGLThread::OpenGLThread() : Thread("OpenGLThread", 60, cedar::QUEUE_BEFORE_TICK, 250)
{
	this->m_window = nullptr;
	this->m_masterRenderer = nullptr;
}

OpenGLThread *OpenGLThread::getInstance()
{
	static OpenGLThread *instance = new OpenGLThread();
	return instance;
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *logger)
{
	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:
			reinterpret_cast<const cedar::Logger*>(logger)->error(message);
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			reinterpret_cast<const cedar::Logger*>(logger)->warn(message);
			break;

		default:
			reinterpret_cast<const cedar::Logger*>(logger)->info(message);
			break;
	}
}

void OpenGLThread::onStart()
{
	this->m_window = new cedar::Window("ToC", 1280, 720, false);
	this->m_window->init(-1);
	this->m_window->setCloseCallback([]() {
		ToC::stop();
	});
	this->m_window->setResizeCallback([=](int newWidth, int newHeight) {
		this->m_masterRenderer->resize();
	});

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, this->m_logger);

	this->m_masterRenderer = new MasterRenderer(this->m_window);
	this->m_masterRenderer->init();

	this->m_window->show();
}

void OpenGLThread::onTick(const unsigned long currentTime, const unsigned long tickCount)
{
	this->m_masterRenderer->render(currentTime, tickCount);
	this->m_window->update();
}

void OpenGLThread::onStop()
{
	this->m_window->close();
	delete this->m_masterRenderer;
	delete this->m_window;
}

cedar::Window *OpenGLThread::getWindow()
{
	return this->m_window;
}