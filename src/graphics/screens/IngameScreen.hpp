//
// Created by masy on 19.04.20.
//

#ifndef TALESOFCATVENTURE_INGAMESCREEN_HPP
#define TALESOFCATVENTURE_INGAMESCREEN_HPP

#include "cedar/Screen.hpp"
#include "cedar/Label.hpp"
#include "cedar/Image.hpp"

using namespace cedar;

/**
 * Class representing the in-game screen.
 */
class IngameScreen : public Screen
{
private:
	/**
	 * A pointer to the health icon.
	 */
	Image *m_healthIcon;
	/**
	 * A pointer to the coin icon.
	 */
	Image *m_coinIcon;

	/**
	 * A pointer to the health label.
	 */
	Label *m_healthLabel;
	/**
	 * A pointer to the coin label.
	 */
	Label *m_coinLabel;
	/**
	 * A pointer to the round label.
	 */
	Label *m_roundLabel;

public:
	/**
	 * Creates a new ingame screen.
	 */
	IngameScreen();

	/**
	 * Deletes the ingame screen.
	 */
	~IngameScreen();

	/**
	 * Initializes the ingame screen.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param guiScale The scale of the gui.
	 */
	void init(int width, int height, int guiScale);
};

#endif //TALESOFCATVENTURE_INGAMESCREEN_HPP
