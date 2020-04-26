//
// Created by masy on 21.03.20.
//

#include <cedar/ModelRegistry.hpp>
#include "EnemyEntity.h"
#include "cedar/EngineThread.hpp"
#include "TDMap.h"

EnemyEntity::EnemyEntity(unsigned int entityId, const unsigned int pathPointCount, const cedar::Vector3f *pathPoints, const EnemyType &type)
		: Entity(entityId, pathPoints[0])
{
	this->m_model = ModelRegistry::getModel("enemy");
	const EnemyInfo *enemyInfo = EnemyInfo::getEnemyInfo(type);
	this->m_maxHealth = enemyInfo->getHealth();
	this->m_health = enemyInfo->getHealth();
	this->m_enemyType = type;
	this->m_tint = enemyInfo->getColor();
	this->m_speed = 0.50f;
	this->m_aiHandler = new AIHandler(pathPointCount - 1, pathPoints, this->m_speed);
}

EnemyEntity::~EnemyEntity()
{
	delete this->m_aiHandler;
}

void EnemyEntity::update(const unsigned long currentTime, const unsigned long tickCount)
{
	if (this->m_aiHandler->reachedGoal())
	{
		this->kill();

		dynamic_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene())->getPlayer()->damage(1);
		return;
	}

	Vector3f newPosition = this->m_aiHandler->getNextPosition();
	this->setPosition(newPosition);
	Entity::update(currentTime, tickCount);
}

EnemyType EnemyEntity::getEnemyType() const
{
	return this->m_enemyType;
}

int EnemyEntity::getMaxHealth() const
{
	return this->m_maxHealth;
}

int EnemyEntity::getHealth() const
{
	return this->m_health;
}

void EnemyEntity::setHealth(int newHealth)
{
	this->m_health = newHealth < 0 ? 0 : (newHealth > this->m_maxHealth ? this->m_maxHealth : newHealth);
	if (this->m_health == 0)
		this->kill();
}

void EnemyEntity::damage(int damageAmount)
{
	this->m_health = std::max(0, this->m_health - damageAmount);
	if (this->m_health == 0)
		this->kill();
}

void EnemyEntity::kill()
{
	cedar::EngineThread::getInstance()->getLoadedScene()->getEntityManager()->removeEntity(this->m_entityId);
}

cedar::Vector3f EnemyEntity::getTint() const
{
	return this->m_tint;
}
