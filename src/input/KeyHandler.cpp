//
// Created by masy on 06.03.20.
//

#include "cedar/Cedar.hpp"
#include "EnemyEntity.h"
#include "KeyHandler.h"
#include "cedar/Input.hpp"
#include "cedar/EngineThread.hpp"
#include "cedar/OpenGLThread.hpp"
#include "cedar/ScreenRegistry.hpp"
#include "cedar/ModelRegistry.hpp"
#include "GameStates.h"
#include "TDMap.h"

KeyHandler::KeyHandler()
= default;

void KeyHandler::init(cedar::InputHandler *inputHandler)
{
}

void KeyHandler::handle(const unsigned long currentTime, const unsigned long tickCount, const cedar::InputHandler *inputHandler)
{
	cedar::Camera *camera = cedar::EngineThread::getInstance()->getCamera();
	unsigned int gameState = cedar::EngineThread::getInstance()->getGameState();

	float deltaTime = static_cast<float>(cedar::OpenGLThread::getInstance()->getLastFrameTime());

	if (camera)
	{
		if (inputHandler->isCursorLocked())
		{
			float yaw = static_cast<float>(inputHandler->getCursorOffsetX()) * deltaTime * 0.25f;
			float pitch = static_cast<float>(inputHandler->getCursorOffsetY()) * deltaTime * 0.25f;

			camera->rotate(pitch, yaw, 0.0f);
		}

		cedar::Vector3f move(0.0f);
		float speed = 25.0f * deltaTime;

		if (inputHandler->isKeyDown(CEDAR_KEY_W))
			move.z -= 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_A))
			move.x -= 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_D))
			move.x += 1.0f;

		if (inputHandler->isKeyDown(CEDAR_KEY_S))
			move.z += 1.0f;

//		if (inputHandler->isKeyDown(CEDAR_KEY_SPACE))
//			move.y += 1.0f;
//
//		if (inputHandler->isKeyDown(CEDAR_KEY_LEFT_SHIFT))
//			move.y -= 1.0f;

		move.normalize();

		move *= speed;
		move.rotateY(-camera->getRotationEuler()->y);
		camera->move(move.x, move.y, move.z);

		camera->zoom(static_cast<float>(inputHandler->getScrollOffsetY()) * -5.0f);
	}

	if (inputHandler->isKeyPressed(CEDAR_KEY_ESCAPE))
	{
		cedar::Screen *screen = cedar::ScreenRegistry::getScreen("escapeScreen");

		TDMap *map = nullptr;
		TowerEntity *selectedTower = nullptr;
		switch (gameState)
		{
			case CEDAR_STATE_RUNNING:
				map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
				if (map)
				{
					selectedTower = map->getSelectedTower();
					if (selectedTower)
					{
						selectedTower->setTint(Vector3f(1.0f, 1.0f, 1.0f));
						map->setSelectedTower(nullptr);
						break;
					}
				}
				screen->setVisibility(true);
				cedar::EngineThread::getInstance()->setGameState(TOC_STATE_MENU);
				break;

			case TOC_STATE_MENU:
				screen->setVisibility(false);
				cedar::EngineThread::getInstance()->setGameState(CEDAR_STATE_RUNNING);
				break;

			case TOC_STATE_PLACING:
				map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
				if (map)
				{
					delete map->getSelectedTower();
					map->setSelectedTower(nullptr);
				}
				cedar::EngineThread::getInstance()->setGameState(CEDAR_STATE_RUNNING);
				break;

			default:
				break;
		}
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

	if (gameState == TOC_STATE_PLACING)
	{
		cedar::Vector3f origin;
		cedar::Vector3f rayDir;

		cedar::OpenGLThread::getInstance()->getMasterRenderer()->getMouseRay(&origin, &rayDir);

		// Calculate where the ray hits y = 0
		float r = - (origin.y / rayDir.y);

		cedar::Vector3f planeIntersection = origin + (rayDir * r);

		Vector3f color(1.0f, 1.0f, 1.0f);
		TDMap *map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
		TowerEntity *selectedTower = nullptr;
		bool isValid = false;
		if (map)
		{
			selectedTower = map->getSelectedTower();
			if (selectedTower)
			{
				selectedTower->setPosition(planeIntersection);
				Vector2f intersection(planeIntersection.x, planeIntersection.z);
				isValid = map->isPositionValid(intersection, selectedTower->getRadius());
				if (!isValid)
					color = Vector3f(1.0f, 0.5f, 0.5f);

				map->getSelectedTower()->setTint(color);
			}
		}

		if (inputHandler->isKeyPressed(CEDAR_MOUSE_BUTTON_LEFT))
		{
			// place ghost tower
			if (isValid)
			{
				map->addTower(selectedTower);
				map->setSelectedTower(nullptr);

				cedar::EngineThread::getInstance()->setGameState(CEDAR_STATE_RUNNING);
			}
		}
	}
	else if (gameState == CEDAR_STATE_RUNNING)
	{
		if (inputHandler->isKeyPressed(CEDAR_KEY_1))
		{
			cedar::Vector3f origin;
			cedar::Vector3f rayDir;

			cedar::OpenGLThread::getInstance()->getMasterRenderer()->getMouseRay(&origin, &rayDir);

			// Calculate where the ray hits y = 0
			float r = - (origin.y / rayDir.y);

			cedar::Vector3f planeIntersection = origin + (rayDir * r);

			TowerEntity *ghostTower = new TowerEntity(cedar::Entity::nextEntityId(), planeIntersection, 1.0f, 0.5f, 10.0f, 0.05f, 1.0f, TOWER_CANON);
			ghostTower->setModel(cedar::ModelRegistry::getModel("tower"));

			TDMap *map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
			map->setSelectedTower(ghostTower);
			cedar::EngineThread::getInstance()->setGameState(TOC_STATE_PLACING);
		}
		else if (inputHandler->isKeyPressed(CEDAR_KEY_2))
		{
			TDMap *map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
			if (map)
			{
				EnemyEntity *enemy = new EnemyEntity(cedar::Entity::nextEntityId(), map->getPathPointCount(), map->getPathPoints(), 1.0f, ENEMY_LEVEL1);
				enemy->setModel(cedar::ModelRegistry::getModel("enemy"));

				map->getEntityManager()->addEntity(enemy);
			}
		}
		else if (inputHandler->isKeyPressed(CEDAR_MOUSE_BUTTON_LEFT))
		{
			TDMap *map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
			if (map)
			{
				cedar::Vector3f origin;
				cedar::Vector3f rayDir;

				cedar::OpenGLThread::getInstance()->getMasterRenderer()->getMouseRay(&origin, &rayDir);

				TowerEntity *oldSelected = map->getSelectedTower();
				TowerEntity *newSelected = map->getTower(origin, rayDir);
				if (oldSelected != newSelected)
				{
					if (newSelected)
					{
						newSelected->setTint(Vector3f(0.7f, 0.7f, 1.0f));
						if (oldSelected)
							oldSelected->setTint(Vector3f(1.0f, 1.0f, 1.0f));
						map->setSelectedTower(newSelected);
					}
					else
					{
						if (oldSelected)
						{
							oldSelected->setTint(Vector3f(1.0f, 1.0f, 1.0f));
							map->setSelectedTower(nullptr);
						}
					}
				}
			}
		}
	}
}
