//
// Created by masy on 26.01.20.
//

#ifndef GUARDIAN_GUARDIAN_H
#define GUARDIAN_GUARDIAN_H

#include "cedar/Cedar.hpp"
#include "GuardianConfig.h"
#include "cedar/Font.hpp"
#include "cedar/MasterRenderer.hpp"

/**
 * The main class of the game.
 */
class Guardian : public Cedar
{
private:

	/**
	 * Creates a new main game object.
	 */
	Guardian();

public:
	/**
	 * A pointer to the configuration of the game.
	 */
	GuardianConfig *m_config;

	/**
	 * Gets the singleton of this class.
	 *
	 * @return A pointer to the Guardian singleton object.
	 */
	static Guardian *getInstance();

	/**
	 * Method which is called before the game starts.
	 */
	void preStart() override;

	/**
	 * Method which is called before all threads are started.
	 */
	void onStart() override;

	/**
	 * Method which is called after all threads have been stopped.
	 */
	void onStop() override;

	/**
	 * Loads the tower defense map.
	 */
	void loadMap() const;

	/**
	 * Initializes the tower information.
	 */
	void initTowers() const;

	/**
	 * Initializes the enemies.
	 */
	void initEnemies() const;

	/**
	 * Initializes the waves.
	 */
	void initWaves() const;

	/**
	 * The initialisation callback of the OpenGL thread.
	 *
	 * @param masterRenderer A pointer to the master renderer.
	 */
	void initCallback(MasterRenderer *masterRenderer);
};

#endif //GUARDIAN_GUARDIAN_H
