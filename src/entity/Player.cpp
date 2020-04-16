//
// Created by masy on 14.04.20.
//

#include "Player.hpp"

Player::Player(int maxHealth, int coins)
{
	this->m_health = maxHealth;
	this->m_coins = coins;
}

int Player::getHealth() const {
	return this->m_health;
}

void Player::damage(const int damage) {
	this->m_health -= damage;
}

void Player::setHealth(const int newHealth) {
	this->m_health = newHealth;
}

int Player::getCoins() const {
	return this->m_coins;
}

void Player::addCoins(const int amount) {
	this->m_coins += amount;
}

void Player::setCoins(const int newCoins)
{
	this->m_coins = newCoins;
}
