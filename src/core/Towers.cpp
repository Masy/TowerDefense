//
// Created by masy on 25.04.20.
//

#include "Towers.hpp"

//---------------------------------------------------------------------------//
//                                 LevelInfo                                 //
//---------------------------------------------------------------------------//

LevelInfo::LevelInfo()
{
	this->m_price = 0;
	this->m_radius = 0.0f;
	this->m_height = 0.0f;
	this->m_damage = 0.0f;
	this->m_attackRadius = 0.0f;
	this->m_attackSpeed = 0;
	this->m_modelName = "";
}

LevelInfo::LevelInfo(const int price, const float radius, const float height, const int damage, const int attackRadius, const int attackSpeed,
					 const std::string &modelName)
{
	this->m_price = price;
	this->m_radius = radius;
	this->m_height = height;
	this->m_damage = damage;
	this->m_attackRadius = attackRadius;
	this->m_attackSpeed = attackSpeed;
}

int LevelInfo::getPrice() const
{
	return this->m_price;
}

void LevelInfo::setPrice(const int newPrice)
{
	this->m_price = newPrice;
}

float LevelInfo::getRadius() const
{
	return this->m_radius;
}

void LevelInfo::setRadius(const float newRadius)
{
	this->m_radius = newRadius;
}

float LevelInfo::getHeight() const
{
	return this->m_height;
}

void LevelInfo::setHeight(const float newHeight)
{
	this->m_height = newHeight;
}

int LevelInfo::getDamage() const
{
	return this->m_damage;
}

void LevelInfo::setDamage(const int newDamage)
{
	this->m_damage = newDamage;
}

int LevelInfo::getAttackRadius() const
{
	return this->m_attackRadius;
}

void LevelInfo::setAttackRadius(const int newAttackRadius)
{
	this->m_attackRadius = newAttackRadius;
}

int LevelInfo::getAttackSpeed() const
{
	return this->m_attackSpeed;
}

void LevelInfo::setAttackSpeed(const int newAttackSpeed)
{
	this->m_attackSpeed = newAttackSpeed;
}

std::string LevelInfo::getModelName() const
{
	return this->m_modelName;
}

void LevelInfo::setModelName(const std::string &newModelName)
{
	this->m_modelName = newModelName;
}

void LevelInfo::set(const int newPrice, const float newRadius, const float newHeight, const int newDamage, const int newAttackRadius,
					const int newAttackSpeed, const std::string &newModelName)
{
	this->m_price = newPrice;
	this->m_radius = newRadius;
	this->m_height = newHeight;
	this->m_damage = newDamage;
	this->m_attackRadius = newAttackRadius;
	this->m_attackSpeed = newAttackSpeed;
	this->m_modelName = newModelName;
}


//---------------------------------------------------------------------------//
//                                 TowerInfo                                 //
//---------------------------------------------------------------------------//

std::map<TowerType, const TowerInfo *> TowerInfo::m_towers = std::map<TowerType, const TowerInfo *>();

TowerInfo::TowerInfo(const std::string &name, int levels, const LevelInfo *levelInfo)
{
	this->m_name = name;
	this->m_levels = levels;
	this->m_levelInfo = levelInfo;
}

TowerInfo::~TowerInfo()
{
	delete[] this->m_levelInfo;
}

std::string TowerInfo::getName() const
{
	return this->m_name;
}

int TowerInfo::getLevels() const
{
	return this->m_levels;
}

const LevelInfo *TowerInfo::getLevelInfo(int level) const
{
	return &this->m_levelInfo[level];
}

void TowerInfo::registerTowerInfo(const TowerType &towerType, const TowerInfo *towerInfo)
{
	m_towers.insert(std::make_pair(towerType, towerInfo));
}

const TowerInfo *TowerInfo::getTowerInfo(const TowerType &towerType)
{
	auto it = m_towers.find(towerType);
	if (it != m_towers.end())
		return it->second;
	else
		return nullptr;
}

void TowerInfo::cleanup()
{
	for (auto &it : m_towers)
	{
		delete it.second;
	}
	m_towers.clear();
}
