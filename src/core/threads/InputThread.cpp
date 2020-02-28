//
// Created by masy on 10.02.20.
//

#include "InputThread.h"
#include "OpenGLThread.h"
#include "EngineThread.h"
#include "cedar/Input.h"
#include "cedar/Vector2d.h"

InputThread::InputThread() : Thread("InputThread", 20, cedar::QUEUE_BEFORE_TICK, 250)
{
	this->m_window = nullptr;
	this->m_inputHandler = nullptr;
	int *forwardKeys = new int[1]{CEDAR_KEY_W};
	this->m_forward = new cedar::KeyCombination(1, forwardKeys);
	int *leftKeys = new int[1]{CEDAR_KEY_A};
	this->m_left = new cedar::KeyCombination(1, leftKeys);
	int *rightKeys = new int[1]{CEDAR_KEY_D};
	this->m_right = new cedar::KeyCombination(1, rightKeys);
	int *backwardsKeys = new int[1]{CEDAR_KEY_S};
	this->m_backwards = new cedar::KeyCombination(1, backwardsKeys);
	int *upwardsKeys = new int[1]{CEDAR_KEY_SPACE};
	this->m_upwards = new cedar::KeyCombination(1, upwardsKeys);
	int *downwardsKeys = new int[1]{CEDAR_KEY_LEFT_SHIFT};
	this->m_downwards = new cedar::KeyCombination(1, downwardsKeys);
	int *menuKeys = new int[1]{256};
	this->m_menu = new cedar::KeyCombination(1, menuKeys);
	int *rightClick = new int[1]{CEDAR_MOUSE_BUTTON_RIGHT};
	this->m_rightClick = new cedar::KeyCombination(1, rightClick);
	this->m_cursorLocked = false;
}

InputThread *InputThread::getInstance()
{
	static InputThread *instance = new InputThread();
	return instance;
}

void InputThread::onStart()
{
	this->m_window = OpenGLThread::getInstance()->getWindow();
	this->m_cursorLocked = this->m_window->isCursorLocked();

	this->m_inputHandler = new cedar::InputHandler(this->m_window);
	this->m_inputHandler->registerKeyCombination(this->m_forward);
	this->m_inputHandler->registerKeyCombination(this->m_left);
	this->m_inputHandler->registerKeyCombination(this->m_right);
	this->m_inputHandler->registerKeyCombination(this->m_backwards);
	this->m_inputHandler->registerKeyCombination(this->m_upwards);
	this->m_inputHandler->registerKeyCombination(this->m_downwards);
	this->m_inputHandler->registerKeyCombination(this->m_menu);
	this->m_inputHandler->registerKeyCombination(this->m_rightClick);
}

void InputThread::onTick(const unsigned long currentTime, const unsigned long tickCount)
{
	this->m_inputHandler->update();
	Camera *camera = EngineThread::getInstance()->getCamera();

	if (this->m_cursorLocked)
	{
		cedar::Vector2d cursorDistance;
		this->m_window->getCursorDistance(&cursorDistance);

		float yaw = static_cast<float>(cursorDistance.x) * 0.002f;
		float pitch = static_cast<float>(cursorDistance.y) * 0.002f;

		camera->rotate(pitch, yaw, 0);
	}

	cedar::Vector3f move(0.0f);
	float speed = 0.5f;

	if (this->m_forward->isDown())
		move.z -= 1.0f;

	if (this->m_left->isDown())
		move.x -= 1.0f;

	if (this->m_right->isDown())
		move.x += 1.0f;

	if (this->m_backwards->isDown())
		move.z += 1.0f;

	if (this->m_upwards->isDown())
		move.y += 1.0f;

	if (this->m_downwards->isDown())
		move.y -= 1.0f;

	move.normalize();

	if (move.lengthSquared() > 0)
	{
		move *= speed;
		camera->moveLocal(move.x, move.y, move.z);
	}

	double scrollY = this->m_window->getScrollOffsetY();
	camera->setZoomLevel(static_cast<int>(camera->getZoomLevel() - scrollY));

	if (this->m_rightClick->isPressed())
	{
		this->m_window->hideCursor(false);
		this->m_cursorLocked = true;
	}
	else if (this->m_rightClick->isReleased())
	{
		this->m_window->showCursor(false);
		this->m_cursorLocked = false;
	}
}

void InputThread::onStop()
{
	delete this->m_inputHandler;
	delete this->m_forward;
	delete this->m_left;
	delete this->m_right;
	delete this->m_backwards;
	delete this->m_upwards;
	delete this->m_downwards;
	delete this->m_menu;
	delete this->m_rightClick;
}