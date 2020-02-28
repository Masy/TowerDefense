//
// Created by masy on 26.01.20.
//

#ifndef TALESOFCATVENTURE_TOC_H
#define TALESOFCATVENTURE_TOC_H

#include <atomic>
#include "ToCConfig.h"

/**
 * The main class of the game.
 */
class ToC
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
	 * Starts the game.
	 *
	 * @param argc The number of program arguments.
	 * @param args The program arguments.
	 */
	void start(int argc, const char **args);
	/**
	 * Stops the game.
	 */
	static void stop();
};

#endif //TALESOFCATVENTURE_TOC_H
