//
// Created by masy on 21.03.20.
//

#ifndef TALESOFCATVENTURE_ENEMYENTITY_H
#define TALESOFCATVENTURE_ENEMYENTITY_H

#include "cedar/Entity.hpp"
#include "AIHandler.h"

using namespace cedar;

enum EnemyType
{
	ENEMY_LEVEL1
};

class EnemyEntity : public cedar::Entity
{
protected:
	float m_maxHealth;
	float m_health;
	EnemyType m_enemyType;
	cedar::Vector3f m_tint;
	AIHandler *m_aiHandler;

public:
	EnemyEntity(unsigned int entityId, unsigned int pathPointCount, const Vector3f *pathPoints, float maxHealth, const EnemyType &type);
	~EnemyEntity();

	void update(unsigned long currentTime, unsigned long tickCount) override;

	[[nodiscard]] float getHealth() const;
	void setHealth(float newHealth);
	void damage(float damageAmount);
	void kill();

	[[nodiscard]] float getMaxHealth() const;
	void setMaxHealth(float newMaxHealth);

	[[nodiscard]] EnemyType getEnemyType() const;

	[[nodiscard]] Vector3f getTint() const;
	void setTint(const Vector3f &newTint);
};

#endif //TALESOFCATVENTURE_ENEMYENTITY_H
