//
// Created by masy on 27.01.20.
//

#ifndef TALESOFCATVENTURE_OPENGLTHREAD_H
#define TALESOFCATVENTURE_OPENGLTHREAD_H

#include "cedar/Thread.h"
#include "MasterRenderer.h"

/**
 * The class of the OpenGL thread.
 *
 * <p>This thread is responsible for rendering and everything OpenGL related like creating models and textures.</p>
 *
 * <p>The tick speed of this thread is depending on the user configuration, but 60 ticks per second is the default speed.</p>
 */
class OpenGLThread : public cedar::Thread
{
private:
	/**
	 * A pointer to the window of the game.
	 */
	cedar::Window *m_window;
	/**
	 * A pointer to the master renderer of the game.
	 */
	MasterRenderer *m_masterRenderer;

	/**
	 * Creates a new OpenGL thread.
	 */
	OpenGLThread();

public:
	/**
	 * Singleton getter to get the instance of the OpenGL thread.
	 *
	 * @return A pointer to the singleton instance of the OpenGL thread.
	 */
	static OpenGLThread *getInstance();
	/**
	 * Method which is called when the OpenGL thread is about to start.
	 *
	 * <p>The OpenGL thread is initialized here.</p>
	 */
	void onStart() override;
	/**
	 * Method which is called every tick of the input thread.
	 *
	 * <p>This will render a frame and/or generate models and textures.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick.
	 */
	void onTick(unsigned long currentTime, unsigned long tickCount) override;
	/**
	 * Method which is called when the OpenGL thread is about to stop.
	 *
	 * <p>The window and all the renderers, models and textures will be cleaned up here.</p>
	 */
	void onStop() override;

	/**
	 * Gets the window of the game.
	 *
	 * @return a pointer to the window of the game.
	 */
	[[nodiscard]] cedar::Window *getWindow();
};

#endif //TALESOFCATVENTURE_OPENGLTHREAD_H
