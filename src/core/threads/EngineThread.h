//
// Created by masy on 27.01.20.
//

#ifndef TALESOFCATVENTURE_ENGINETHREAD_H
#define TALESOFCATVENTURE_ENGINETHREAD_H

#include "cedar/Thread.h"
#include "Camera.h"

/**
 * The class of the engine thread.
 *
 * <p>The engine thread is responsible for handling entities and everything that other threads don't handle.</p>
 *
 * <p>This thread ticks at a speed of 20 ticks per second.</p>
 */
class EngineThread : public cedar::Thread
{
private:
	/**
	 * A pointer to the camera instance.
	 */
	Camera *m_camera;

	/**
	 * Creates a new engine thread.
	 */
	EngineThread();

public:
	/**
	 * Singleton getter to get the instance of the engine thread.
	 *
	 * @return A pointer to the singleton instance of the engine thread.
	 */
	static EngineThread *getInstance();

	/**
	 * Method which is called when the engine thread is about to start.
	 *
	 * <p>The engine thread is initialized here.</p>
	 */
	void onStart() override;

	/**
	 * Method which is called every tick of the engine thread.
	 *
	 * <p>This will handle the game state machine and entity updates.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick.
	 */
	void onTick(unsigned long currentTime, unsigned long tickCount) override;

	/**
	 * Method which is called when the engine thread is about to stop.
	 *
	 * <p>Everything the entity thread handled will be cleaned up here.</p>
	 */
	void onStop() override;

	/**
	 * Gets the camera object.
	 *
	 * @return A pointer to the camera object.
	 */
	[[nodiscard]] Camera *getCamera() const;
};

#endif //TALESOFCATVENTURE_ENGINETHREAD_H
