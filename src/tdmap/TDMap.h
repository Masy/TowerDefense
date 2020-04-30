//
// Created by masy on 11.03.20.
//

#ifndef GUARDIAN_TDMAP_H
#define GUARDIAN_TDMAP_H

#include "cedar/Scene.hpp"
#include "cedar/MeshCollider2D.hpp"
#include "TowerEntity.h"
#include "Player.hpp"
#include "Waves.hpp"

using namespace cedar;

/**
 * Class representing the tower defense map.
 */
class TDMap : public Scene
{
private:
	/**
	 * A pointer to the player.
	 */
	Player *m_player;
	/**
	 * A pointer to the two dimensional mesh collider of the area the player is not allowed to place towers on.
	 */
	MeshCollider2D *m_noBuildZone;
	/**
	 * The number of points in the path array.
	 */
	unsigned int m_pathPointCount;
	/**
	 * A pointer to the array of path points.
	 */
	const Vector3f *m_pathPoints;

	/**
	 * List of currently placed towers.
	 */
	std::vector<TowerEntity *> m_towers;
	/**
	 * A pointer to the currently selected tower.
	 */
	TowerEntity *m_selectedTower;
	/**
	 * A pointer to a transformation matrix.
	 */
	Matrix4f *m_transformationMatrix;

	/**
	 * The current wave.
	 */
	int m_currentWave;
	/**
	 * A constant pointer to the information about the current wave.
	 */
	const WaveInfo *m_currentWaveInfo;
	/**
	 * The enemy index of the current wave.
	 */
	int m_waveEnemyIndex;

public:
	/**
	 * Creates a new tower defense map.
	 *
	 * @param position The position of the map.
	 * @param player A pointer to the player.
	 * @param model A pointer to the model of the map
	 * @param noBuildZone A pointer to the mesh collider of the no build zone.
	 * @param pathPointCount The number of points on the path.
	 * @param pathPoints A constant pointer to the array of points on the path.
	 */
	TDMap(const Vector3f &position, Player *player, Model *model, MeshCollider2D *noBuildZone, unsigned int pathPointCount,
		  const Vector3f *pathPoints);

	/**
	 * Destroys the tower defense map.
	 */
	~TDMap() override;

	/**
	 * Checks whether the given position is a valid location.
	 *
	 * @param position The position that will be checked.
	 * @param radius The radius around the position that will be taken into consideration.
	 * @return Whether the position is valid or not.
	 */
	[[nodiscard]] bool isPositionValid(const Vector2f &position, float radius) const;

	/**
	 * Gets the first tower entity that intersects with the given ray.
	 *
	 * @param cameraOrigin The position of the camera.
	 * @param rayDir The direction of the ray.
	 * @return A pointer to the first tower entity that was hit by the ray or <code>nullptr</code> if there is none.
	 */
	[[nodiscard]] TowerEntity *getTower(const Vector3f &cameraOrigin, const Vector3f &rayDir);

	/**
	 * Updates the map.
	 *
	 * <p>This method is called 20 times per second from the engine thread.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick count.
	 */
	void update(unsigned long currentTime, unsigned long tickCount) override;

	/**
	 * Renders the map, enemies and towers.
	 *
	 * @param currentTime The current time in microseconds.
	 * @param tickCount The current tick count.
	 * @param shader A pointer to the shader that is currently bound.
	 */
	void render(unsigned long currentTime, unsigned long tickCount, const ShaderProgram *shader) override;

	/**
	 * Adds a tower to the map.
	 *
	 * @param towerEntity A pointer to the tower that will be added.
	 */
	void addTower(TowerEntity *towerEntity);

	/**
	 * Removes a tower from the map.
	 *
	 * @param towerEntity A pointer to the tower that will be removed.
	 */
	void removeTower(TowerEntity *towerEntity);

	/**
	 * Gets the currently selected tower.
	 *
	 * @return A pointer to the currently selected tower.
	 */
	[[nodiscard]] TowerEntity *getSelectedTower() const;

	/**
	 * Sets the currently selected tower.
	 *
	 * @param newSelectedTower A pointer to the new selected tower.
	 */
	void setSelectedTower(TowerEntity *newSelectedTower);

	/**
	 * Gets the number of points on the path of the map.
	 *
	 * @return The number of points on the path of the map.
	 */
	[[nodiscard]] unsigned int getPathPointCount() const;

	/**
	 * Gets the array of path points.
	 *
	 * @return A constant pointer to the array of path points.
	 */
	[[nodiscard]] const Vector3f *getPathPoints() const;

	/**
	 * Starts the next wave.
	 */
	void startNextWave();

	/**
	 * Restarts the game.
	 *
	 * <p>This will delete all enemies adn towers, reset the current wave to 0 and resets the players health and coins.</p>
	 */
	void restart();

	/**
	 * Gets the player.
	 *
	 * @return A pointer to the player.
	 */
	[[nodiscard]] Player *getPlayer() const;
};

#endif //GUARDIAN_TDMAP_H
