//
// Created by masy on 11.03.20.
//

#include <limits>
#include <EnemyEntity.h>
#include <cedar/ModelRegistry.hpp>
#include <IngameScreen.hpp>
#include <cedar/ScreenRegistry.hpp>

#include "TDMap.h"
#include "cedar/Distance2D.hpp"

#define RAY_LENGTH 64.0f

TDMap::TDMap(const cedar::Vector3f &position, Player *player, cedar::Model *model, cedar::MeshCollider2D *noBuildZone,
			 const unsigned int pathPointCount,
			 const cedar::Vector3f *pathPoints) : Scene(position)
{
	this->m_player = player;
	this->m_noBuildZone = noBuildZone;
	this->m_pathPointCount = pathPointCount;
	this->m_pathPoints = pathPoints;
	this->m_models.push_back(model);
	this->m_selectedTower = nullptr;
	this->m_transformationMatrix = new cedar::Matrix4f();
	this->m_currentWave = 0;
	this->m_currentWaveInfo = nullptr;
	this->m_waveEnemyIndex = 0;
}

TDMap::~TDMap()
{
	delete this->m_player;
	delete this->m_entityManager;
	delete[] this->m_pathPoints;
	for (auto towerEntity : this->m_towers)
		delete towerEntity;
	this->m_towers.clear();

	delete this->m_selectedTower;
	delete this->m_transformationMatrix;
}

bool TDMap::isPositionValid(const cedar::Vector2f &position, const float radius) const
{
	float radiusSquared = radius * radius;
	float combinedRadius;
	for (TowerEntity *tower : this->m_towers)
	{
		cedar::Vector3f towerPos = tower->getPosition();
		cedar::Vector2f towerPos2D(towerPos.x, towerPos.z);

		combinedRadius = tower->getRadius() * tower->getRadius() + radiusSquared;
		float distanceSquared = towerPos2D.distance(position);
		if (distanceSquared < combinedRadius)
			return false;
	}

	return !this->m_noBuildZone->intersectsCircle(position, radius);
}

TowerEntity *TDMap::getTower(const cedar::Vector3f &cameraOrigin, const cedar::Vector3f &rayDir)
{
	unsigned int towerCount = this->m_towers.size();
	if (towerCount > 0)
	{
		float distances[towerCount];
		for (int n = 0; n < towerCount; n++)
			distances[n] = std::numeric_limits<float>::max();

		TowerEntity *sortedTowers[towerCount];

		// Sort towers by distance to camera
		float distanceSquared;
		int index = 0;
		for (TowerEntity *tower : this->m_towers)
		{
			distanceSquared = cameraOrigin.distanceSquared(tower->getPosition());

			for (int n = 0; n <= index; n++)
			{
				if (distanceSquared <= distances[n])
				{
					for (int m = index; m >= n; m--)
					{
						distances[m + 1] = distances[m];
						sortedTowers[m + 1] = sortedTowers[m];
					}
					distances[n] = distanceSquared;
					sortedTowers[n] = tower;
					break;
				}
			}
			index++;
		}

		cedar::Vector2f origin2D(cameraOrigin.x, cameraOrigin.z);
		cedar::Vector2f rayDir2d(rayDir.x, rayDir.z);
		cedar::Vector3f towerPosition;
		for (index = 0; index < towerCount; index++)
		{
			TowerEntity *tower = sortedTowers[index];
			tower->getPosition(&towerPosition);

			cedar::Vector2f circleCenter(towerPosition.x, towerPosition.z);
			float radiusSquared = tower->getRadius() * tower->getRadius();

			distanceSquared = cedar::distanceSquaredPointToLineSegment(origin2D, origin2D + rayDir2d * RAY_LENGTH, circleCenter);
			if (distanceSquared <= radiusSquared) // the ray could potentially hit the cylinder of the tower
			{
				// check if ray intersects with bottom of cylinder
				float length = (towerPosition.y - cameraOrigin.y) / rayDir.y;
				cedar::Vector3f intersection = cameraOrigin + length * rayDir;
				distanceSquared = intersection.distanceSquared(towerPosition);

				if (distanceSquared <= radiusSquared)
					return tower;

				// check if ray intersects with top of cylinder
				length = (towerPosition.y + tower->getHeight() - cameraOrigin.y) / rayDir.y;
				intersection = cameraOrigin + length * rayDir;
				distanceSquared = intersection.distanceSquared(towerPosition + cedar::Vector3f(0.0f, tower->getHeight(), 0.0f));

				if (distanceSquared <= radiusSquared)
					return tower;

				// check if ray intersects with lateral surface of cylinder
				cedar::Vector3f startToEnd = cameraOrigin + rayDir * RAY_LENGTH;
				cedar::Vector2f posToStart = origin2D - cedar::Vector2f(towerPosition.x, towerPosition.z);

				float a = startToEnd.xz().lengthSquared();
				float b = 2.0f * posToStart.dot(startToEnd.xz());
				float c = posToStart.lengthSquared() - radiusSquared;

				float discriminant = b * b - 4 * a * c;
				if (discriminant < 0.0)
				{
					continue;
				}
				else
				{
					discriminant = std::sqrt(discriminant);

					float minY = towerPosition.y;
					float maxY = towerPosition.y + tower->getHeight();

					b = -b;
					a = 2 * a;
					float t1 = (b - discriminant) / a;
					float t2 = (b + discriminant) / a;

					float intersectionY = 0.0f;
					if (t1 >= 0.0f && t1 <= 1.0f)
					{
						intersectionY = cameraOrigin.y + t1 * startToEnd.y;
						if (intersectionY >= minY && intersectionY <= maxY)
							return tower;
					}

					if (t2 >= 0.0f && t2 <= 1.0f)
					{
						intersectionY = cameraOrigin.y + t2 * startToEnd.y;
						if (intersectionY >= minY && intersectionY <= minY)
							return tower;
					}
				}
			}
		}
	}

	return nullptr;
}

void TDMap::update(const unsigned long currentTime, const unsigned long tickCount)
{
	if (this->m_waveEnemyIndex != 0 && this->m_player->getHealth() <= 0)
	{
		this->m_currentWaveInfo = nullptr;
		this->m_waveEnemyIndex = 0;
		IngameScreen *ingameScreen = dynamic_cast<IngameScreen*>(ScreenRegistry::getScreen("ingameScreen"));
		ingameScreen->setSelectedTower(nullptr);
		ingameScreen->setVisibility(false);
		ScreenRegistry::getScreen("gameOverScreen")->setVisibility(true);
	}

	if (this->m_player->getHealth() > 0)
	{
		Scene::update(currentTime, tickCount);

		for (TowerEntity *tower : this->m_towers)
		{
			tower->update(currentTime, tickCount);
		}

		// If the selected tower is already placed it was updated by the for loop
		if (this->m_selectedTower && !this->m_selectedTower->isPlaced())
			this->m_selectedTower->update(currentTime, tickCount);

		if (this->m_currentWaveInfo != nullptr)
		{
			if (this->m_waveEnemyIndex < this->m_currentWaveInfo->getEnemyCount())
			{
				if (tickCount % 5 == 0)
				{
					EnemyType nextEnemy = this->m_currentWaveInfo->getEnemies()[this->m_waveEnemyIndex++];
					if (nextEnemy != NONE)
					{
						EnemyEntity *enemy = new EnemyEntity(cedar::Entity::nextEntityId(), this->m_pathPointCount, this->m_pathPoints, nextEnemy);
						this->m_entityManager->addEntity(enemy);
					}
				}
			}
			else
			{
				this->m_currentWaveInfo = nullptr;
			}
		}
		else if (this->m_entityManager->getEntities()->empty())
		{
			dynamic_cast<IngameScreen *>(ScreenRegistry::getScreen("ingameScreen"))->setStartWaveButtonEnabled(true);
			if (this->m_currentWave == WaveInfo::getWaveCount())
			{
				IngameScreen *ingameScreen = dynamic_cast<IngameScreen*>(ScreenRegistry::getScreen("ingameScreen"));
				ingameScreen->setSelectedTower(nullptr);
				ingameScreen->setVisibility(false);
				ScreenRegistry::getScreen("winScreen")->setVisibility(true);
			}
		}
	}
}

void TDMap::render(const unsigned long currentTime, const unsigned long tickCount, const cedar::ShaderProgram *shader)
{
	int transformationUniform = shader->getUniformLocation("u_transformationMatrix");
	int tintUniform = shader->getUniformLocation("u_tint");

	cedar::Vector3f position = this->m_position;
	shader->setUniform3f(tintUniform, 1.0f, 1.0f, 1.0f);
	for (cedar::Model *model : this->m_models)
	{
		this->m_transformationMatrix->translation(&position);
		shader->setUniform4x4f(transformationUniform, *this->m_transformationMatrix);
		model->render();
	}

	cedar::Model *towerModel;
	for (TowerEntity *tower : this->m_towers)
	{
		towerModel = tower->getModel();
		if (towerModel)
		{
			position = this->m_position + tower->getPosition();
			this->m_transformationMatrix->translation(&position);
			shader->setUniform4x4f(transformationUniform, *this->m_transformationMatrix);
			shader->setUniform3f(tintUniform, tower->getTint());
			towerModel->render();
		}
	}

	// If the selected tower is already placed it was rendered by the for loop
	if (this->m_selectedTower && !this->m_selectedTower->isPlaced())
	{
		towerModel = this->m_selectedTower->getModel();
		if (towerModel)
		{
			position = this->m_position + this->m_selectedTower->getPosition();
			this->m_transformationMatrix->translation(&position);
			shader->setUniform4x4f(transformationUniform, *this->m_transformationMatrix);
			shader->setUniform3f(tintUniform, this->m_selectedTower->getTint());
			towerModel->render();
		}
	}

	auto it = this->m_entityManager->getEntities()->cbegin();
	while (it != this->m_entityManager->getEntities()->cend())
	{
		Model *model = it->second->getModel();
		if (model)
		{
			position = this->m_position + it->second->getLerpedPosition(currentTime);
			this->m_transformationMatrix->translation(&position);
			shader->setUniform4x4f(transformationUniform, *this->m_transformationMatrix);
			shader->setUniform3f(tintUniform, dynamic_cast<EnemyEntity *>(it->second.get())->getTint());
			model->render();
		}

		it++;
	}
}

void TDMap::addTower(TowerEntity *towerEntity)
{
	for (auto &m_tower : this->m_towers)
	{
		if (m_tower == towerEntity)
			return;
	}

	this->m_towers.push_back(towerEntity);
}

void TDMap::removeTower(TowerEntity *towerEntity)
{
	for (auto it = this->m_towers.begin(); it != this->m_towers.end(); it++)
	{
		if ((*it) == towerEntity)
		{
			this->m_towers.erase(it);
			return;
		}
	}
}

TowerEntity *TDMap::getSelectedTower() const
{
	return this->m_selectedTower;
}

void TDMap::setSelectedTower(TowerEntity *newSelectedTower)
{
	this->m_selectedTower = newSelectedTower;
}

unsigned int TDMap::getPathPointCount() const
{
	return this->m_pathPointCount;
}

const cedar::Vector3f *TDMap::getPathPoints() const
{
	return this->m_pathPoints;
}

void TDMap::startNextWave()
{
	if (this->m_currentWave < WaveInfo::getWaveCount())
	{
		this->m_waveEnemyIndex = 0;
		this->m_currentWave++;
		this->m_currentWaveInfo = WaveInfo::getWaveInfo(this->m_currentWave);
		dynamic_cast<IngameScreen *>(ScreenRegistry::getScreen("ingameScreen"))->setCurrentWave(this->m_currentWave);
	}
}

void TDMap::restart()
{
	this->m_currentWave = 0;
	this->m_currentWaveInfo = nullptr;
	this->m_waveEnemyIndex = 0;
	dynamic_cast<IngameScreen *>(ScreenRegistry::getScreen("ingameScreen"))->setCurrentWave(this->m_currentWave);
	this->m_player->setCoins(225);
	this->m_player->setHealth(20);

	this->m_selectedTower = nullptr;
	for (auto towerEntity : this->m_towers)
		delete towerEntity;
	this->m_towers.clear();
	this->m_entityManager->cleanup();
}

Player *TDMap::getPlayer() const
{
	return this->m_player;
}
