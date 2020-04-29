//
// Created by masy on 06.03.20.
//

#ifndef GUARDIAN_KEYHANDLER_H
#define GUARDIAN_KEYHANDLER_H

#include "cedar/InputHandler.hpp"

/**
 * The key handler of the game.
 */
class KeyHandler
{
private:
	/**
	 * Creates a new key handler.
	 */
	KeyHandler();

public:
	/**
	 * Initialized the key handler.
	 *
	 * @param inputHandler A pointer to the input handler of the game.
	 */
	static void init(cedar::InputHandler *inputHandler);

	/**
	 * Handles the input of the game.
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current amount of ticks.
	 * @param inputHandler A constant pointer to the input handler of the game.
	 */
	static void handle(unsigned long currentTime, unsigned long tickCount, const cedar::InputHandler *inputHandler);
};

#endif //GUARDIAN_KEYHANDLER_H
