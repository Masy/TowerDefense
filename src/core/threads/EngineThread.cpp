//
// Created by masy on 27.01.20.
//

#include "EngineThread.h"
#include <iostream>

EngineThread::EngineThread() : Thread("EngineThread", 20, cedar::QUEUE_BEFORE_TICK, 250)
{
	this->m_camera = nullptr;
}

EngineThread *EngineThread::getInstance()
{
	static EngineThread *instance = new EngineThread();
	return instance;
}

void EngineThread::onStart()
{
	this->m_camera = new Camera();
}

void EngineThread::onTick(const unsigned long currentTime, const unsigned long tickCount)
{
	this->m_camera->update(currentTime);
}

void EngineThread::onStop()
{
	delete this->m_camera;
}

Camera *EngineThread::getCamera() const
{
	return this->m_camera;
}