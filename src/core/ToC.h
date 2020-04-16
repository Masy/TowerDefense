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
	Vector4f cloudWhite;
	Vector4f gray;
	Vector4f background;
	Vector4f hoverBlue;
	Vector4f pressBlue;
	Vector4f hoverRed;
	Vector4f pressRed;
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

	void createDebugScreen(cedar::Font *font);

	void createEscapeScreen(cedar::Font *font);

	void createIngameScreen(cedar::Font *font, float guiScale);

	void loadMap();

	void initCallback(MasterRenderer *masterRenderer);
};

#endif //TALESOFCATVENTURE_TOC_H
