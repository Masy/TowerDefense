//
// Created by masy on 25.04.20.
//

#ifndef TALESOFCATVENTURE_TOWERS_HPP
#define TALESOFCATVENTURE_TOWERS_HPP

#include <string>
#include <map>

/**
 * Enum storing all types of towers.
 */
enum TowerType
{
	TOWER_CANON
};

/**
 * Class storing information about the level of a certain tower.
 */
class LevelInfo
{
private:
	/**
	 * The price of the tower to upgrade to that level.
	 */
	int m_price;
	/**
	 * The radius of the tower in that level.
	 */
	float m_radius;
	/**
	 * The height of the tower in that level.
	 */
	float m_height;
	/**
	 * The damage of the tower in that level.
	 */
	int m_damage;
	/**
	 * The attack radius of the tower in that level.
	 */
	int m_attackRadius;
	/**
	 * The attack speed of the tower in that level.
	 */
	int m_attackSpeed;
	/**
	 * The name of the tower's model in that level.
	 */
	std::string m_modelName;

public:
	/**
	 * Creates a new level info.
	 */
	LevelInfo();

	/**
	 * Creates a new level info.
	 *
	 * @param price The price of the tower in that level.
	 * @param radius The radius of the tower in that level.
	 * @param height The height of the tower in that level.
	 * @param damage The damage of the tower in that level.
	 * @param attackRadius The attack radius of the tower in that level.
	 * @param attackSpeed The attack speed of the tower in that level.
	 * @param modelName The name of the tower's model in that level.
	 */
	LevelInfo(int price, float radius, float height, int damage, int attackRadius, int attackSpeed, const std::string &modelName);

	/**
	 * Gets the price of the tower in that level.
	 *
	 * @return The price of the tower.
	 */
	[[nodiscard]] int getPrice() const;

	/**
	 * Sets the price of the tower in that level.
	 *
	 * @param newPrice The new price of the tower.
	 */
	void setPrice(int newPrice);

	/**
	 * Gets the radius of the tower in that level.
	 *
	 * @return The radius of the tower.
	 */
	[[nodiscard]] float getRadius() const;

	/**
	 * Sets the radius of the tower in that level.
	 *
	 * @param newRadius The new radius of the tower.
	 */
	void setRadius(float newRadius);

	/**
	 * Gets the height of the tower in that level.
	 *
	 * @return The height of the tower.
	 */
	[[nodiscard]] float getHeight() const;

	/**
	 * Sets the height of the tower in that level.
	 *
	 * @param newHeight The new height of the tower.
	 */
	void setHeight(float newHeight);

	/**
	 * Sets the damage of the tower in that level.
	 *
	 * @return The damage of the tower.
	 */
	[[nodiscard]] int getDamage() const;

	/**
	 * Sets the damage of the tower in that level.
	 *
	 * @param newDamage The new damage of the tower.
	 */
	void setDamage(int newDamage);

	/**
	 * Gets the attack radius of the tower in that level.
	 *
	 * @return The attack radius of the tower.
	 */
	[[nodiscard]] int getAttackRadius() const;

	/**
	 * Sets the attack radius of the tower in that level.
	 *
	 * @param newAttackRadius The new attack radius of the tower.
	 */
	void setAttackRadius(int newAttackRadius);

	/**
	 * Gets the attack speed of the tower in that level.
	 *
	 * @return The attack speed of the tower.
	 */
	[[nodiscard]] int getAttackSpeed() const;

	/**
	 * Sets the attack speed of the tower in that level.
	 *
	 * @param newAttackSpeed The new attack speed of the tower.
	 */
	void setAttackSpeed(int newAttackSpeed);

	/**
	 * Gets the name of the tower's model in that level.
	 *
	 * @return The name of the tower's model.
	 */
	[[nodiscard]] std::string getModelName() const;

	/**
	 * Sets the name of the tower's model in that level.
	 *
	 * @param newModelName The new name of the tower's model.
	 */
	void setModelName(const std::string &newModelName);

	/**
	 * Sets the information about the tower in that level.
	 *
	 * @param newPrice The new price of the tower.
	 * @param newRadius The new radius of the tower.
	 * @param newHeight The new height of the tower.
	 * @param newDamage The new damage of the tower.
	 * @param newAttackRadius The new attack radius of the tower.
	 * @param newAttackSpeed The new attack speed of the tower.
	 * @param newModelName The new name of the tower's model.
	 */
	void set(int newPrice, float newRadius, float newHeight, int newDamage, int newAttackRadius, int newAttackSpeed, const std::string &newModelName);
};

/**
 * Class storing information about a tower.
 */
class TowerInfo
{
private:
	/**
	 * Map for storing tower information about each tower type.
	 */
	static std::map<TowerType, const TowerInfo *> m_towers;

	/**
	 * The name of the tower.
	 */
	std::string m_name;
	/**
	 * The number of levels the tower has.
	 */
	unsigned int m_levels;
	/**
	 * The information about each level.
	 */
	const LevelInfo *m_levelInfo;

public:
	/**
	 * Creates a new tower information.
	 *
	 * @param name The name of the tower.
	 * @param levels The number of levels the tower has.
	 * @param levelInfo A pointer to the array of level information.
	 */
	TowerInfo(const std::string &name, unsigned int levels, const LevelInfo *levelInfo);

	/**
	 * Deletes the tower information.
	 */
	~TowerInfo();

	/**
	 * Gets the name of the tower.
	 *
	 * @return The name of the tower.
	 */
	[[nodiscard]] std::string getName() const;

	/**
	 * Gets the number of levels of the tower.
	 *
	 * @return The number of levels of the tower.
	 */
	[[nodiscard]] unsigned int getLevels() const;

	/**
	 * Gets the information about a level of the tower..
	 *
	 * @param level The level of the tower the information will be about.
	 * @return A constant pointer to the level information about the tower level.
	 */
	[[nodiscard]] const LevelInfo *getLevelInfo(unsigned int level) const;

	/**
	 * Registers the given tower information for the tower type.
	 *
	 * @param towerType The tower type the information is for.
	 * @param towerInfo A constant pointer to the tower information.
	 */
	static void registerTowerInfo(const TowerType &towerType, const TowerInfo *towerInfo);

	/**
	 * Gets the information about a tower type.
	 *
	 * @param towerType The tower type the information will be about.
	 * @return A constant pointer to the information about the tower.
	 */
	static const TowerInfo *getTowerInfo(const TowerType &towerType);

	/**
	 * Cleans up the tower information map.
	 */
	static void cleanup();
};


#endif //TALESOFCATVENTURE_TOWERS_HPP
