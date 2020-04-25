//
// Created by masy on 12.03.20.
//

#include "TowerEntity.h"
#include <cedar/EngineThread.hpp>
#include <cedar/ModelRegistry.hpp>
#include "TDMap.h"
#include "EnemyEntity.h"

TowerEntity::TowerEntity(const unsigned int entityId, const cedar::Vector3f &position, const TowerType &towerType)
		: Entity(entityId, position)
{
	const LevelInfo *levelInfo = TowerInfo::getTowerInfo(towerType)->getLevelInfo(0);
	this->m_model = ModelRegistry::getModel(levelInfo->getModelName());
	this->m_radius = levelInfo->getRadius();
	this->m_height = levelInfo->getHeight();
	this->m_level = 0;
	this->m_attackRadius = levelInfo->getAttackRadius();
	this->m_attackSpeed = levelInfo->getAttackSpeed();
	this->m_damage = levelInfo->getDamage();
	this->m_towerType = towerType;
	this->m_attackTick = static_cast<unsigned long>(20 / this->m_attackSpeed);
	this->m_placed = false;
	this->m_ticksAlive = 0;
}

void TowerEntity::update(const unsigned long currentTime, const unsigned long tickCount)
{
	if (this->m_placed)
	{
		TDMap *map = dynamic_cast<TDMap *>(cedar::EngineThread::getInstance()->getLoadedScene());

		float radiusSquared = this->m_attackRadius * this->m_attackRadius;

		auto it = map->getEntityManager()->getEntities()->begin();
		for (const auto &pair : *map->getEntityManager()->getEntities())
		{
			std::shared_ptr<Entity> entity = pair.second;
			if (entity->getPosition().distanceSquared(this->m_position) < radiusSquared)
			{
				if (this->m_ticksAlive % this->m_attackTick == 0)
				{
					EnemyEntity *enemy = dynamic_cast<EnemyEntity *>(entity.get());
					enemy->damage(static_cast<float>(this->m_damage));
					if (enemy->getHealth() == 0.0f)
					{
						map->getPlayer()->addCoins(1);
					}
				}
				break;
			}
		}
	}

	this->m_lastUpdate = currentTime;
	this->m_ticksAlive++;
}

float TowerEntity::getRadius() const
{
	return this->m_radius;
}

float TowerEntity::getHeight() const
{
	return this->m_height;
}

unsigned int TowerEntity::getLevel() const
{
	return this->m_level;
}

void TowerEntity::setLevel(unsigned int newLevel)
{
	const TowerInfo *towerInfo = TowerInfo::getTowerInfo(this->m_towerType);

	newLevel = std::min(newLevel, towerInfo->getLevels() - 1);

	if (newLevel != this->m_level)
	{
		this->m_level = newLevel;

		const LevelInfo *levelInfo = towerInfo->getLevelInfo(newLevel);
		this->m_damage = levelInfo->getDamage();
		this->m_attackRadius = levelInfo->getAttackRadius();
		this->m_attackSpeed = levelInfo->getAttackSpeed();
		this->m_attackTick = static_cast<unsigned long>(20 / levelInfo->getAttackSpeed());
		this->m_model = ModelRegistry::getModel(levelInfo->getModelName());
	}
}

int TowerEntity::getAttackRadius() const
{
	return this->m_attackRadius;
}

int TowerEntity::getAttackSpeed() const
{
	return this->m_attackSpeed;
}

int TowerEntity::getDamage() const
{
	return this->m_damage;
}

TowerType TowerEntity::getTowerType() const
{
	return this->m_towerType;
}

cedar::Vector3f TowerEntity::getTint() const
{
	return this->m_tint;
}

void TowerEntity::setTint(const cedar::Vector3f &newTint)
{
	this->m_tint = newTint;
}

bool TowerEntity::isPlaced() const
{
	return this->m_placed;
}

void TowerEntity::setPlaced(const bool isPlaced)
{
	this->m_placed = isPlaced;
}
