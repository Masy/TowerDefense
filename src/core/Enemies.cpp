//
// Created by masy on 26.04.20.
//

#include "Enemies.hpp"

std::map<EnemyType, const EnemyInfo *> EnemyInfo::m_enemies = std::map<EnemyType, const EnemyInfo *>();

EnemyInfo::EnemyInfo(const int health, const Vector3f &color)
{
	this->m_health = health;
	this->m_color = color;
}

int EnemyInfo::getHealth() const
{
	return this->m_health;
}

Vector3f EnemyInfo::getColor() const
{
	return this->m_color;
}

void EnemyInfo::registerEnemyInfo(const EnemyType &enemyType, const EnemyInfo *enemyInfo)
{
	m_enemies[enemyType] = enemyInfo;
}

const EnemyInfo *EnemyInfo::getEnemyInfo(const EnemyType &enemyType)
{
	auto it = m_enemies.find(enemyType);
	if (it != m_enemies.end())
		return it->second;
	else
		return nullptr;
}

void EnemyInfo::cleanup()
{
	for (auto &it : m_enemies)
	{
		delete it.second;
	}
	m_enemies.clear();
}
