//
// Created by masy on 27.01.20.
//

#ifndef TALESOFCATVENTURE_WORLDTHREAD_H
#define TALESOFCATVENTURE_WORLDTHREAD_H

#include "cedar/Thread.h"

/**
 * The class of the world thread.
 *
 * <p>The world thread is responsible for loading/unloading, saving and updating the world.</p>
 *
 * <p>This thread ticks at a speed of 20 ticks per second.</p>
 */
class WorldThread : public cedar::Thread
{
private:
	/**
	 * Creates a new world thread.
	 */
	WorldThread();

public:
	/**
	 * Singleton getter to get the instance of the world thread.
	 *
	 * @return A pointer to the singleton instance of the world thread.
	 */
	static WorldThread *getInstance();
	/**
	 * Method which is called when the world thread is about to start.
	 *
	 * <p>The world thread is initialized here.</p>
	 */
	void onStart() override;
	/**
	 * Method which is called every tick of the world thread.
	 *
	 * <p>This will update the world if it is loaded.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick.
	 */
	void onTick(unsigned long currentTime, unsigned long tickCount) override;
	/**
	 * Method which is called when the world thread is about to stop.
	 *
	 * <p>The world will be saved and cleaned up here if it is loaded.</p>
	 */
	void onStop() override;
};

#endif //TALESOFCATVENTURE_WORLDTHREAD_H
