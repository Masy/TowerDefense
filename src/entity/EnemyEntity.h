//
// Created by masy on 21.03.20.
//

#ifndef TALESOFCATVENTURE_ENEMYENTITY_H
#define TALESOFCATVENTURE_ENEMYENTITY_H

#include "cedar/Entity.hpp"
#include "AIHandler.h"
#include "Enemies.hpp"

using namespace cedar;

class EnemyEntity : public cedar::Entity
{
protected:
	EnemyType m_enemyType;
	int m_maxHealth;
	int m_health;
	Vector3f m_tint;
	AIHandler *m_aiHandler;

public:
	EnemyEntity(unsigned int entityId, unsigned int pathPointCount, const Vector3f *pathPoints, const EnemyType &type);

	~EnemyEntity();

	void update(unsigned long currentTime, unsigned long tickCount) override;

	[[nodiscard]] EnemyType getEnemyType() const;

	[[nodiscard]] int getMaxHealth() const;

	[[nodiscard]] int getHealth() const;

	void setHealth(int newHealth);

	void damage(int damageAmount);

	void kill();

	[[nodiscard]] Vector3f getTint() const;
};

#endif //TALESOFCATVENTURE_ENEMYENTITY_H
