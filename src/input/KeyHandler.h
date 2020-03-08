//
// Created by masy on 06.03.20.
//

#ifndef TALESOFCATVENTURE_KEYHANDLER_H
#define TALESOFCATVENTURE_KEYHANDLER_H

#include "cedar/InputHandler.h"

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
	 * @param inputHandler A constant pointer to the input handler of the game.
	 */
	static void handle(const cedar::InputHandler *inputHandler);
};

#endif //TALESOFCATVENTURE_KEYHANDLER_H
