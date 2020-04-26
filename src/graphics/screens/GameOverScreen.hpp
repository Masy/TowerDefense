//
// Created by masy on 26.04.20.
//

#ifndef TALESOFCATVENTURE_GAMEOVERSCREEN_HPP
#define TALESOFCATVENTURE_GAMEOVERSCREEN_HPP

#include "cedar/Screen.hpp"
#include "cedar/Label.hpp"
#include "cedar/ImageButton.hpp"

using namespace cedar;

/**
 * Class representing the game over screen.
 */
class GameOverScreen : public Screen
{
private:
	/**
	 * A pointer to the game over text label.
	 */
	Label *m_gameOverLabel;
	/**
	 * A pointer to the restart button.
	 */
	ImageButton *m_restartButton;

public:
	/**
	 * Creates a new game over screen.
	 */
	GameOverScreen();

	/**
	 * Deletes the game over screen.
	 */
	~GameOverScreen();

	/**
	 * Initializes the game over screen.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param guiScale The scale of the gui.
	 */
	void init(int width, int height, int scale);
};

#endif //TALESOFCATVENTURE_GAMEOVERSCREEN_HPP
