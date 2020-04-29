//
// Created by masy on 14.04.20.
//

#ifndef GUARDIAN_PLAYER_HPP
#define GUARDIAN_PLAYER_HPP

class Player
{
private:
	int m_health;
	int m_coins;

public:
	Player(int maxHealth, int coins);

	[[nodiscard]] int getHealth() const;

	void damage(int damage);

	void setHealth(int newHealth);

	[[nodiscard]] int getCoins() const;

	void addCoins(int amount);

	void setCoins(int newCoins);
};

#endif //GUARDIAN_PLAYER_HPP
