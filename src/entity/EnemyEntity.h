//
// Created by masy on 21.03.20.
//

#ifndef GUARDIAN_ENEMYENTITY_H
#define GUARDIAN_ENEMYENTITY_H

#include "cedar/Entity.hpp"
#include "AIHandler.h"
#include "Enemies.hpp"

using namespace cedar;

/**
 * Class representing an enemy entity.
 */
class EnemyEntity : public Entity
{
protected:
	/**
	 * The type of the enemy.
	 */
	EnemyType m_enemyType;
	/**
	 * The maximum health of the enemy.
	 */
	int m_maxHealth;
	/**
	 * The current health of the enemy.
	 */
	int m_health;
	/**
	 * The tint of the enemy.
	 */
	Vector3f m_tint;
	/**
	 * A pointer to the AI handler of the enemy.
	 */
	AIHandler *m_aiHandler;

public:
	/**
	 * Creates a new enemy entity.
	 *
	 * @param entityId The entity id of the enemy.
	 * @param pathPointCount The number of path points the enemy walks along.
	 * @param pathPoints A constant pointer to the array of path points.
	 * @param type The type of the enemy.
	 */
	EnemyEntity(unsigned int entityId, unsigned int pathPointCount, const Vector3f *pathPoints, const EnemyType &type);

	/**
	 * Destroys the enemy.
	 */
	~EnemyEntity();

	/**
	 * Updates the enemy.
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick count.
	 */
	void update(unsigned long currentTime, unsigned long tickCount) override;

	/**
	 * Gets the type of the enemy.
	 *
	 * @return The type of the enemy.
	 */
	[[nodiscard]] EnemyType getEnemyType() const;

	/**
	 * Gets the maximum health of the enemy.
	 *
	 * @return The maximum health of the enemy.
	 */
	[[nodiscard]] int getMaxHealth() const;

	/**
	 * Gets the current health of the enemy.
	 *
	 * @return The current health of the enemy.
	 */
	[[nodiscard]] int getHealth() const;

	/**
	 * Sets the current health of the enemy.
	 *
	 * @param newHealth The new health of the enemy.
	 */
	void setHealth(int newHealth);

	/**
	 * Damages the enemy.
	 *
	 * @param damageAmount The amount of damage that is applied to the enemy.
	 */
	void damage(int damageAmount);

	/**
	 * Kills the enemy.
	 */
	void kill();

	/**
	 * Gets the tint of the enemy.
	 *
	 * @return The tint of the enemy.
	 */
	[[nodiscard]] Vector3f getTint() const;
};

#endif //GUARDIAN_ENEMYENTITY_H
