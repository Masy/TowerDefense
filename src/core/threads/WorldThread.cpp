//
// Created by masy on 27.01.20.
//

#include "WorldThread.h"
#include <iostream>

WorldThread::WorldThread() : Thread("WorldThread", 20, cedar::QUEUE_BEFORE_TICK, 250)
{}

WorldThread *WorldThread::getInstance()
{
	static WorldThread *instance = new WorldThread();
	return instance;
}

void WorldThread::onStart()
{
}

void WorldThread::onTick(const unsigned long currentTime, const unsigned long tickCount)
{

}

void WorldThread::onStop()
{
}

