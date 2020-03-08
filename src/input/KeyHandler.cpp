//
// Created by masy on 06.03.20.
//

#include "KeyHandler.h"
#include "cedar/Input.h"
#include "cedar/EngineThread.h"
#include "cedar/OpenGLThread.h"
#include "cedar/ScreenRegistry.h"

KeyHandler::KeyHandler()
= default;

void KeyHandler::init(cedar::InputHandler *inputHandler)
{
}

void KeyHandler::handle(const cedar::InputHandler *inputHandler)
{
	cedar::Camera *camera = cedar::EngineThread::getInstance()->getCamera();

	float deltaTime = static_cast<float>(cedar::OpenGLThread::getInstance()->getLastFrameTime());

	if (camera)
	{
		if (inputHandler->isCursorLocked())
		{
			float yaw = static_cast<float>(inputHandler->getCursorOffsetX()) * deltaTime * 0.25f;
			float pitch = static_cast<float>(inputHandler->getCursorOffsetY()) * deltaTime * 0.25f;

				camera->rotate(pitch, yaw, 0.0f);
		}

		float yaw = 0.0;
		if (inputHandler->isKeyDown(CEDAR_KEY_D))
			yaw += 1.5f;

		if (inputHandler->isKeyDown(CEDAR_KEY_A))
			yaw -= 1.5f;

		yaw *= deltaTime;
		camera->rotateY(yaw);

		cedar::Vector3f move(0.0f);
		float speed = 100.0f * deltaTime;

		if (inputHandler->isKeyDown(CEDAR_KEY_W))
			move.z -= 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_Q))
			move.x -= 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_E))
			move.x += 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_S))
			move.z += 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_SPACE))
			move.y += 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_LEFT_SHIFT))
			move.y -= 1.0f;

		move.normalize();

		move *= speed;
		move.rotateY(-camera->getRotationEuler()->y);
		camera->move(move.x, move.y, move.z);

		camera->zoom(static_cast<float>(inputHandler->getScrollOffsetY()) * -5.0f);
	}

	if (inputHandler->isKeyPressed(CEDAR_KEY_ESCAPE))
	{
		cedar::Screen *screen = cedar::ScreenRegistry::getScreen("screen");
		screen->setVisibility(!screen->isVisible());
	}

	if (inputHandler->isKeyPressed(CEDAR_KEY_F3))
	{
		cedar::Screen *screen = cedar::ScreenRegistry::getScreen("debug");
		screen->setVisibility(!screen->isVisible());
	}

	cedar::Window *window = cedar::OpenGLThread::getInstance()->getWindow();
	if (inputHandler->isKeyPressed(CEDAR_MOUSE_BUTTON_RIGHT))
	{
		window->hideCursor(false);
	}
	else if (inputHandler->isKeyReleased(CEDAR_MOUSE_BUTTON_RIGHT))
	{
		window->showCursor(false);
	}
}
