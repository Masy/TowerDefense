//
// Created by masy on 10.02.20.
//

#ifndef TALESOFCATVENTURE_INPUTTHREAD_H
#define TALESOFCATVENTURE_INPUTTHREAD_H

#include "cedar/Thread.h"
#include "cedar/InputHandler.h"
#include "cedar/Window.h"

/**
 * The class of the input thread.
 *
 * <p>The input thread is responsible for polling mouse and key events and to process them.</p>
 *
 * <p>This thread ticks at a speed of 20 ticks per second.</p>
 */
class InputThread : public cedar::Thread
{
private:
	/**
	 * A pointer to the window of the game.
	 */
	cedar::Window *m_window;
	/**
	 * A pointer to the input handler of the game.
	 */
	cedar::InputHandler *m_inputHandler;
	/**
	 * A pointer to the key combination that moves the camera forward.
	 */
	cedar::KeyCombination *m_forward;
	/**
	 * A pointer to the key combination that moves the camera right.
	 */
	cedar::KeyCombination *m_right;
	/**
	 * A pointer to the key combination that moves the camera left.
	 */
	cedar::KeyCombination *m_left;
	/**
	 * A pointer to the key combination that moves the camera backwards.
	 */
	cedar::KeyCombination *m_backwards;
	/**
	 * A pointer to the key combination that moves the camera upwards.
	 */
	cedar::KeyCombination *m_upwards;
	/**
	 * A pointer to the key combination that moves the camera downwards.
	 */
	cedar::KeyCombination *m_downwards;
	/**
	 * A pointer to the key combination that opens the menu.
	 */
	cedar::KeyCombination *m_menu;
	/**
	 * A pointer to the right click key combination.
	 */
	cedar::KeyCombination *m_rightClick;

	/**
	 * Whether the cursor of the window is locked or not.
	 */
	bool m_cursorLocked;

	/**
	 * Creates a new input thread.
	 */
	InputThread();

public:
	/**
	 * Singleton getter to get the instance of the input thread.
	 *
	 * @return A pointer to the singleton instance of the input thread.
	 */
	static InputThread *getInstance();
	/**
	 * Method which is called when the input thread is about to start.
	 *
	 * <p>The input thread is initialized here.</p>
	 */
	void onStart() override;
	/**
	 * Method which is called every tick of the input thread.
	 *
	 * <p>This will poll events and process them.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick.
	 */
	void onTick(unsigned long currentTime, unsigned long tickCount) override;
	/**
	 * Method which is called when the input thread is about to stop.
	 *
	 * <p>All the key combinations and the input handler will be cleaned up here.</p>
	 */
	void onStop() override;
};

#endif //TALESOFCATVENTURE_INPUTTHREAD_H
