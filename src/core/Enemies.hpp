//
// Created by masy on 26.04.20.
//

#ifndef GUARDIAN_ENEMIES_HPP
#define GUARDIAN_ENEMIES_HPP

#include <map>
#include "cedar/Vector3f.hpp"

using namespace cedar;

/**
 * Enum storing all types of enemies.
 */
enum EnemyType
{
	NONE = -1,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	LEVEL7,
	LEVEL8,
	LEVEL9
};

/**
 * Class storing information about an enemy.
 */
class EnemyInfo
{
private:
	/**
	 * Map for storing enemy information about each enemy.
	 */
	static std::map<EnemyType, const EnemyInfo *> m_enemies;

	/**
	 * The health of the enemy.
	 */
	int m_health;
	/**
	 * The color of the enemy.
	 */
	Vector3f m_color;

public:
	/**
	 * Creates a new enemy information.
	 *
	 * @param health The health of the enemy.
	 * @param color The color of the enemy.
	 */
	EnemyInfo(int health, const Vector3f &color);

	/**
	 * Gets the health of the enemy.
	 *
	 * @return The health of the enemy.
	 */
	[[nodiscard]] int getHealth() const;

	/**
	 * Gets the color of the enemy.
	 *
	 * @return The color of the enemy.
	 */
	[[nodiscard]] Vector3f getColor() const;

	/**
	 * Registers the given enemy information for the enemy type.
	 *
	 * @param enemyType The enemy type the information is for.
	 * @param enemyInfo A constant pointer to the enemy information.
	 */
	static void registerEnemyInfo(const EnemyType &enemyType, const EnemyInfo *enemyInfo);

	/**
	 * Gets the information about an enemy type.
	 *
	 * @param enemyType The enemy type the information will be about.
	 * @return A constant pointer to the information about the enemy.
	 */
	static const EnemyInfo *getEnemyInfo(const EnemyType &enemyType);

	/**
	 * Cleans up the enemy information map.
	 */
	static void cleanup();
};

#endif //GUARDIAN_ENEMIES_HPP
