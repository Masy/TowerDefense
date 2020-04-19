//
// Created by masy on 26.01.20.
//

#ifndef TALESOFCATVENTURE_TOC_H
#define TALESOFCATVENTURE_TOC_H

#include "cedar/Cedar.hpp"
#include "ToCConfig.h"
#include "cedar/Font.hpp"
#include "cedar/MasterRenderer.hpp"

/**
 * The main class of the game.
 */
class ToC : public Cedar
{
private:

	/**
	 * Creates a new main game object.
	 */
	ToC();

public:
	/**
	 * A pointer to the configuration of the game.
	 */
	ToCConfig *m_config;

	/**
	 * Gets the singleton of this class.
	 *
	 * @return A pointer to the ToC singleton object.
	 */
	static ToC *getInstance();

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
	void loadMap();

	/**
	 * The initialisation callback of the OpenGL thread.
	 *
	 * @param masterRenderer A pointer to the master renderer.
	 */
	void initCallback(MasterRenderer *masterRenderer);
};

#endif //TALESOFCATVENTURE_TOC_H
