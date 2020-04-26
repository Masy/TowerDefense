//
// Created by masy on 12.03.20.
//

#ifndef TALESOFCATVENTURE_TOWERENTITY_H
#define TALESOFCATVENTURE_TOWERENTITY_H

#include "cedar/Entity.hpp"
#include "Towers.hpp"

/**
 * Class representing a tower entity.
 */
class TowerEntity : public cedar::Entity
{
protected:
	/**
	 * The type of the tower.
	 */
	TowerType m_towerType;
	/**
	 * The radius of the tower.
	 *
	 * <p>This is used to calculated intersection related things since a cylinder is used to save performance.</p>
	 */
	float m_radius;
	/**
	 * The height of the tower.
	 *
	 * <p>This is used to calculated intersection related things since a cylinder is used to save performance.</p>
	 */
	float m_height;
	/**
	 * The current level of the tower.
	 */
	unsigned int m_level;
	/**
	 * The current attack radius of the tower.
	 */
	int m_attackRadius;
	/**
	 * The current attack speed of the tower.
	 */
	int m_attackSpeed;
	/**
	 * The current damage of the tower.
	 */
	int m_damage;
	/**
	 * The tick at which the tower is allowed to attack.
	 *
	 * <p>This is calculated based on the {@link #m_attackSpeed attack speed} of the tower.</p>
	 */
	unsigned long m_attackTick;
	/**
	 * The tint of the tower.
	 */
	cedar::Vector3f m_tint;
	/**
	 * Whether the tower is placed or not.
	 */
	bool m_placed;
	/**
	 * The lifetime of the tower in ticks.
	 */
	int m_ticksAlive;

public:
	/**
	 * Creates a new tower entity.
	 *
	 * @param entityId The entity id of the tower.
	 * @param position The position of the tower.
	 * @param towerType The type of the tower.
	 */
	TowerEntity(unsigned int entityId, const cedar::Vector3f &position, const TowerType &towerType);

	/**
	 * Updates the entity.
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick count.
	 */
	void update(unsigned long currentTime, unsigned long tickCount) override;

	/**
	 * Gets the type of the tower.
	 *
	 * @return The type of the tower.
	 */
	[[nodiscard]] TowerType getTowerType() const;

	/**
	 * Gets the radius of the tower.
	 *
	 * @return The radius of the tower.
	 */
	[[nodiscard]] float getRadius() const;

	/**
	 * Gets the height of the tower.
	 *
	 * @return The height of the tower.
	 */
	[[nodiscard]] float getHeight() const;

	/**
	 * Gets the level of the tower.
	 *
	 * @return The level of the tower.
	 */
	[[nodiscard]] unsigned int getLevel() const;

	/**
	 * Sets the level of the tower.
	 *
	 * <p>If the <code>new level</code> is greater than the max level of the tower type the level will be set to the max level instead.</p>
	 *
	 * @param newLevel The new level of the tower.
	 */
	void setLevel(unsigned int newLevel);

	/**
	 * Gets the attack radius of the tower.
	 *
	 * @return The attack radius of the tower.
	 */
	[[nodiscard]] int getAttackRadius() const;

	/**
	 * Gets the attack speed of the tower.
	 *
	 * @return The attack speed of the tower.
	 */
	[[nodiscard]] int getAttackSpeed() const;

	/**
	 * Gets the damage of the tower.
	 *
	 * @return The damage of the tower.
	 */
	[[nodiscard]] int getDamage() const;

	/**
	 * Gets the tint of the tower.
	 *
	 * @return The tint of the tower.
	 */
	[[nodiscard]] cedar::Vector3f getTint() const;

	/**
	 * Sets the tint of the tower.
	 *
	 * @param newTint The new tint of the tower.
	 */
	void setTint(const cedar::Vector3f &newTint);

	/**
	 * Checks whether the tower is placed or not.
	 *
	 * @return Whether the tower is placed or not.
	 */
	[[nodiscard]] bool isPlaced() const;

	/**
	 * Sets whether the tower is placed or not.
	 *
	 * @param isPlaced Whether the tower will be placed or not.
	 */
	void setPlaced(bool isPlaced);

};

#endif //TALESOFCATVENTURE_TOWERENTITY_H
