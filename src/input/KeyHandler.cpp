//
// Created by masy on 06.03.20.
//

#include "KeyHandler.h"
#include "cedar/Input.h"
#include "cedar/EngineThread.h"
#include "cedar/OpenGLThread.h"
#include "cedar/Cedar.h"

cedar::KeyCombination *KeyHandler::keyForward = nullptr;
cedar::KeyCombination *KeyHandler::keyRight = nullptr;
cedar::KeyCombination *KeyHandler::keyLeft = nullptr;
cedar::KeyCombination *KeyHandler::keyBackwards = nullptr;
cedar::KeyCombination *KeyHandler::keyUpwards = nullptr;
cedar::KeyCombination *KeyHandler::keyDownwards = nullptr;
cedar::KeyCombination *KeyHandler::keyMenu = nullptr;
cedar::KeyCombination *KeyHandler::keyRightClick = nullptr;

KeyHandler::KeyHandler()
= default;

void KeyHandler::init(cedar::InputHandler *inputHandler)
{
	int *forwardKeys = new int[1]{CEDAR_KEY_W};
	keyForward = new cedar::KeyCombination(1, forwardKeys);
	inputHandler->registerKeyCombination(keyForward);

	int *leftKeys = new int[1]{CEDAR_KEY_A};
	keyLeft = new cedar::KeyCombination(1, leftKeys);
	inputHandler->registerKeyCombination(keyLeft);

	int *rightKeys = new int[1]{CEDAR_KEY_D};
	keyRight = new cedar::KeyCombination(1, rightKeys);
	inputHandler->registerKeyCombination(keyRight);

	int *backwardsKeys = new int[1]{CEDAR_KEY_S};
	keyBackwards = new cedar::KeyCombination(1, backwardsKeys);
	inputHandler->registerKeyCombination(keyBackwards);

	int *upwardsKeys = new int[1]{CEDAR_KEY_SPACE};
	keyUpwards = new cedar::KeyCombination(1, upwardsKeys);
	inputHandler->registerKeyCombination(keyUpwards);

	int *downwardsKeys = new int[1]{CEDAR_KEY_LEFT_SHIFT};
	keyDownwards = new cedar::KeyCombination(1, downwardsKeys);
	inputHandler->registerKeyCombination(keyDownwards);

	int *menuKeys = new int[1]{256};
	keyMenu = new cedar::KeyCombination(1, menuKeys);
	inputHandler->registerKeyCombination(keyMenu);

	int *rightClick = new int[1]{CEDAR_MOUSE_BUTTON_RIGHT};
	keyRightClick = new cedar::KeyCombination(1, rightClick);
	inputHandler->registerKeyCombination(keyRightClick);
}

void KeyHandler::handle(cedar::InputHandler *inputHandler)
{
	cedar::Camera *camera = cedar::EngineThread::getInstance()->getCamera();

	cedar::Window *window = cedar::OpenGLThread::getInstance()->getWindow();
	if (camera)
	{
		if (window->isCursorLocked())
		{
			cedar::Vector2d cursorDistance;
			window->getCursorDistance(&cursorDistance);

			float yaw = static_cast<float>(cursorDistance.x) * 0.002f;
			float pitch = static_cast<float>(cursorDistance.y) * 0.002f;

			camera->rotate(pitch, yaw, 0);
		}

		cedar::Vector3f move(0.0f);
		float speed = 0.5f;

		if (keyForward->isDown())
			move.z -= 1.0f;

		if (keyLeft->isDown())
			move.x -= 1.0f;

		if (keyRight->isDown())
			move.x += 1.0f;

		if (keyBackwards->isDown())
			move.z += 1.0f;

		if (keyUpwards->isDown())
			move.y += 1.0f;

		if (keyDownwards->isDown())
			move.y -= 1.0f;

		move.normalize();

		if (move.lengthSquared() > 0)
		{
			move *= speed;
			camera->moveLocal(move.x, move.y, move.z);
		}

		camera->zoom(static_cast<float>(window->getScrollOffsetY()) * -5.0f);
	}

	if (keyRightClick->isPressed())
	{
		window->hideCursor(false);
	}
	else if (keyRightClick->isReleased())
	{
		window->showCursor(false);
	}
}

void KeyHandler::cleanup()
{
	delete keyForward;
	delete keyLeft;
	delete keyRight;
	delete keyBackwards;
	delete keyUpwards;
	delete keyDownwards;
	delete keyMenu;
	delete keyRightClick;
}
