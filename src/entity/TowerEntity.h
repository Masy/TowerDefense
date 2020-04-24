//
// Created by masy on 12.03.20.
//

#ifndef TALESOFCATVENTURE_TOWERENTITY_H
#define TALESOFCATVENTURE_TOWERENTITY_H

#include "cedar/Entity.hpp"

enum TowerType
{
	TOWER_CANON,
	TOWER_MAGIC,
	TOWER_TESLA,
	TOWER_FREEZER
};

class TowerEntity : public cedar::Entity
{
protected:
	float m_radius;
	float m_height;
	float m_attackRadius;
	float m_attackSpeed;
	float m_damage;
	unsigned long m_attackTick;
	TowerType m_towerType;
	cedar::Vector3f m_tint;
	bool m_placed;

	int m_ticksAlive;

public:
	TowerEntity(unsigned int entityId, const cedar::Vector3f &position, float radius, float m_height, float attackRadius, float attackSpeed, float damage, TowerType towerType);

	/**
	 * Updates the entity.
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick count.
	 */
	void update(unsigned long currentTime, unsigned long tickCount) override;

	[[nodiscard]] float getRadius() const;
	[[nodiscard]] float getHeight() const;
	void setHeight(float newHeight);

	[[nodiscard]] float getAttackRadius() const;
	void setAttackRadius(float newAttackRadius);

	[[nodiscard]] float getAttackSpeed() const;
	void setAttackSpeed(float newAttackSpeed);

	[[nodiscard]] float getDamage() const;
	void setDamage(float newDamage);

	[[nodiscard]] TowerType getTowerType() const;

	[[nodiscard]] cedar::Vector3f getTint() const;
	void setTint(const cedar::Vector3f &newTint);

	[[nodiscard]] bool isPlaced() const;

	void setPlaced(bool isPlaced);

};

#endif //TALESOFCATVENTURE_TOWERENTITY_H
