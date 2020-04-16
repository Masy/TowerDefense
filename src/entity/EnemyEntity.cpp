//
// Created by masy on 21.03.20.
//

#include <cedar/Cedar.hpp>
#include <TDMap.h>
#include "EnemyEntity.h"
#include "cedar/EngineThread.hpp"
#include "cedar/Math.hpp"

EnemyEntity::EnemyEntity(unsigned int entityId, const unsigned int pathPointCount, const cedar::Vector3f *pathPoints, float maxHealth, const EnemyType &type)
		: Entity(entityId, pathPoints[0])
{
	this->m_maxHealth = maxHealth;
	this->m_health = maxHealth;
	this->m_enemyType = type;
	this->m_tint = cedar::Vector3f(1.0f, 1.0f, 1.0f);
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

float EnemyEntity::getHealth() const
{
	return this->m_health;
}

void EnemyEntity::setHealth(float newHealth)
{
	this->m_health = cedar::clamp(newHealth, 0.0f, this->m_maxHealth);
	if (this->m_health == 0.0f)
		this->kill();
}

void EnemyEntity::damage(float damageAmount)
{
	this->m_health = std::max(0.0f, this->m_health - damageAmount);
	if (this->m_health == 0.0f)
		this->kill();
}

void EnemyEntity::kill()
{
	cedar::EngineThread::getInstance()->getLoadedScene()->getEntityManager()->removeEntity(this->m_entityId);
}

float EnemyEntity::getMaxHealth() const
{
	return this->m_maxHealth;
}

void EnemyEntity::setMaxHealth(float newMaxHealth)
{
	this->m_maxHealth = newMaxHealth;
	if (this->m_health > newMaxHealth)
		this->m_health = newMaxHealth;
}

EnemyType EnemyEntity::getEnemyType() const
{
	return this->m_enemyType;
}

cedar::Vector3f EnemyEntity::getTint() const
{
	return this->m_tint;
}

void EnemyEntity::setTint(const cedar::Vector3f &newTint)
{
	this->m_tint = newTint;
}
