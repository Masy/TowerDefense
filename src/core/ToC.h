//
// Created by masy on 26.01.20.
//

#ifndef TALESOFCATVENTURE_TOC_H
#define TALESOFCATVENTURE_TOC_H

#include "cedar/Cedar.h"
#include "ToCConfig.h"

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

	void preStart() override;
	void onStart() override;
	void onStop() override;
};

#endif //TALESOFCATVENTURE_TOC_H
