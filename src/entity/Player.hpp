//
// Created by masy on 14.04.20.
//

#ifndef GUARDIAN_PLAYER_HPP
#define GUARDIAN_PLAYER_HPP

/**
 * Class for storing information about the player.
 */
class Player
{
private:
	/**
	 * The health of the player.
	 */
	int m_health;
	/**
	 * The coins of the player.
	 */
	int m_coins;

public:
	/**
	 * Creates a new player.
	 *
	 * @param maxHealth The health of the player.
	 * @param coins The coins of the player.
	 */
	Player(int maxHealth, int coins);

	/**
	 * Gets the health of the player.
	 *
	 * @return The health of the player.
	 */
	[[nodiscard]] int getHealth() const;

	/**
	 * Damages the player.
	 *
	 * @param damage The amount of damage applied to the player.
	 */
	void damage(int damage);

	/**
	 * Sets the health of the player.
	 *
	 * @param newHealth The new health of the player.
	 */
	void setHealth(int newHealth);

	/**
	 * Gets the coins of the player.
	 *
	 * @return The coins of the player.
	 */
	[[nodiscard]] int getCoins() const;

	/**
	 * Adds the given amount of coins to the player.
	 *
	 * @param amount The amount of coins that will be added to the player.
	 */
	void addCoins(int amount);

	/**
	 * Sets the amount of coins the player has.
	 *
	 * @param newCoins The new amount of coins the player has.
	 */
	void setCoins(int newCoins);
};

#endif //GUARDIAN_PLAYER_HPP
