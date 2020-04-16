//
// Created by masy on 12.03.20.
//

#include <cedar/EngineThread.hpp>
#include <TDMap.h>
#include "TowerEntity.h"
#include "EnemyEntity.h"

TowerEntity::TowerEntity(const unsigned int entityId, const cedar::Vector3f &position, const float radius, const float height, const float attackRadius,
						 const float attackSpeed, const float damage, const TowerType towerType) : Entity(entityId, position)
{
	this->m_radius = radius;
	this->m_height = height;
	this->m_attackRadius = attackRadius;
	this->m_attackSpeed = attackSpeed;
	this->m_damage = damage;
	this->m_towerType = towerType;
	this->m_attackTick = static_cast<unsigned long>(1.0 / attackSpeed);
	this->m_ticksAlive = 0;
}

void TowerEntity::update(const unsigned long currentTime, const unsigned long tickCount)
{
	TDMap *map = dynamic_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());

	float radiusSquared = this->m_attackRadius * this->m_attackRadius;

	auto it = map->getEntityManager()->getEntities()->begin();
	for (const auto &pair : *map->getEntityManager()->getEntities())
	{
		std::shared_ptr<Entity> entity = pair.second;
		if (entity->getPosition().distanceSquared(this->m_position) < radiusSquared)
		{
			if (this->m_ticksAlive % this->m_attackTick == 0)
			{
				EnemyEntity *enemy = dynamic_cast<EnemyEntity*>(entity.get());
				enemy->damage(this->m_damage);
				if (enemy->getHealth() == 0.0f)
				{
					map->getPlayer()->addCoins(1);
				}
			}
			break;
		}
	}

	this->m_lastUpdate = currentTime;
	this->m_ticksAlive++;
}

float TowerEntity::getRadius() const
{
	return this->m_radius;
}

float TowerEntity::getHeight() const {
	return this->m_height;
}

void TowerEntity::setHeight(const float newHeight) {
	this->m_height = newHeight;
}

float TowerEntity::getAttackRadius() const
{
	return this->m_attackRadius;
}

void TowerEntity::setAttackRadius(const float newAttackRadius)
{
	this->m_attackRadius = newAttackRadius;
}

float TowerEntity::getAttackSpeed() const
{
	return this->m_attackSpeed;
}

void TowerEntity::setAttackSpeed(const float newAttackSpeed)
{
	this->m_attackSpeed = newAttackSpeed;
}

float TowerEntity::getDamage() const
{
	return this->m_damage;
}

void TowerEntity::setDamage(const float newDamage)
{
	this->m_damage = newDamage;
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
