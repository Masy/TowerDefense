//
// Created by masy on 26.04.20.
//

#include "Waves.hpp"

std::map<unsigned int, const WaveInfo *> WaveInfo::m_waves = std::map<unsigned int, const WaveInfo *>();

WaveInfo::WaveInfo(const unsigned int enemyCount, EnemyType *enemies)
{
	this->m_enemyCount = enemyCount;
	this->m_enemies = enemies;
}

WaveInfo::~WaveInfo()
{
	delete[] this->m_enemies;
}

unsigned int WaveInfo::getEnemyCount() const
{
	return this->m_enemyCount;
}

const EnemyType *WaveInfo::getEnemies() const
{
	return this->m_enemies;
}

void WaveInfo::registerWaveInfo(const unsigned int waveIndex, const WaveInfo *waveInfo)
{
	m_waves[waveIndex] = waveInfo;
}

const WaveInfo *WaveInfo::getWaveInfo(const unsigned int waveIndex)
{
	auto it = m_waves.find(waveIndex);
	if (it != m_waves.end())
		return it->second;
	else
		return nullptr;
}

unsigned int WaveInfo::getWaveCount()
{
	return m_waves.size();
}

void WaveInfo::cleanup()
{
	for (auto &it : m_waves)
	{
		delete it.second;
	}
	m_waves.clear();
}
