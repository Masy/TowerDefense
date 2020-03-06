//
// Created by masy on 06.03.20.
//

#ifndef TALESOFCATVENTURE_KEYHANDLER_H
#define TALESOFCATVENTURE_KEYHANDLER_H

#include "cedar/InputHandler.h"

class KeyHandler
{
private:
	/**
	 * A pointer to the key combination that moves the camera forward.
	 */
	static cedar::KeyCombination *keyForward;
	/**
	 * A pointer to the key combination that moves the camera right.
	 */
	static cedar::KeyCombination *keyRight;
	/**
	 * A pointer to the key combination that moves the camera left.
	 */
	static cedar::KeyCombination *keyLeft;
	/**
	 * A pointer to the key combination that moves the camera backwards.
	 */
	static cedar::KeyCombination *keyBackwards;
	/**
	 * A pointer to the key combination that moves the camera upwards.
	 */
	static cedar::KeyCombination *keyUpwards;
	/**
	 * A pointer to the key combination that moves the camera downwards.
	 */
	static cedar::KeyCombination *keyDownwards;
	/**
	 * A pointer to the key combination that opens the menu.
	 */
	static cedar::KeyCombination *keyMenu;
	/**
	 * A pointer to the right click key combination.
	 */
	static cedar::KeyCombination *keyRightClick;

	/**
	 * Creates a new key handler.
	 */
	KeyHandler();

public:
	static void init(cedar::InputHandler *inputHandler);
	static void handle(cedar::InputHandler *inputHandler);
	static void cleanup();
};

#endif //TALESOFCATVENTURE_KEYHANDLER_H
