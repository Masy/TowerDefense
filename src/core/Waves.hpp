//
// Created by masy on 26.04.20.
//

#ifndef GUARDIAN_WAVES_HPP
#define GUARDIAN_WAVES_HPP

#include "Enemies.hpp"

/**
 * Class storing about a wave.
 */
class WaveInfo
{
private:
	/**
	 * Map for storing information about each wave.
	 */
	static std::map<unsigned int, const WaveInfo *> m_waves;

	/**
	 * The number of enemies in the wave.
	 */
	unsigned int m_enemyCount;
	/**
	 * A pointer to the array of enemies that are spawned during the wave.
	 */
	EnemyType *m_enemies;

public:
	/**
	 * Creates a new wave information.
	 *
	 * @param enemyCount The number of enemies in the wave.
	 * @param enemies A pointer to the array enemies that are spawned during the wave.
	 */
	WaveInfo(unsigned int enemyCount, EnemyType *enemies);

	/**
	 * Deletes the wave information.
	 */
	~WaveInfo();

	/**
	 * Gets the number of enemies in the wave.
	 *
	 * @return The number of enemies in the wave.
	 */
	[[nodiscard]] unsigned int getEnemyCount() const;

	/**
	 * Gets the array of enemies that are spawned during the wave.
	 *
	 * @return A constant pointer to the array of enemies that are spawned during the wave.
	 */
	[[nodiscard]] const EnemyType *getEnemies() const;

	/**
	 * Registers the given wave information for the wave index.
	 *
	 * @param waveIndex The index the information is for.
	 * @param waveInfo A constant pointer to the wave information.
	 */
	static void registerWaveInfo(unsigned int waveIndex, const WaveInfo *waveInfo);

	/**
	 * Gets the information about the wave index.
	 *
	 * @param waveIndex The wave index the information will be about.
	 * @return A constant pointer to the information about the wave.
	 */
	static const WaveInfo *getWaveInfo(unsigned int waveIndex);

	/**
	 * Gets the number of registered waves..
	 *
	 * @return The number of registered waves.
	 */
	static unsigned int getWaveCount();

	/**
	 * Cleans up the wave information map.
	 */
	static void cleanup();
};

#endif //GUARDIAN_WAVES_HPP
