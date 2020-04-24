//
// Created by masy on 19.04.20.
//

#ifndef TALESOFCATVENTURE_ESCAPESCREEN_HPP
#define TALESOFCATVENTURE_ESCAPESCREEN_HPP

#include "cedar/Screen.hpp"
#include "cedar/ImageButton.hpp"

using namespace cedar;

/**
 * Class representing the escape screen.
 */
class EscapeScreen : public Screen
{
private:
	/**
	 * A pointer to the option button.
	 */
	ImageButton *m_optionButton;
	/**
	 * A pointer to the close button.
	 */
	ImageButton *m_closeButton;
	/**
	 * A pointer to the exit button.
	 */
	ImageButton *m_exitButton;

public:
	/**
	 * Creates a new escape screen.
	 */
	EscapeScreen();

	/**
	 * Deletes the escape screen.
	 */
	~EscapeScreen();

	/**
	 * Initializes the escape screen.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param scale The scale of the gui.
	 */
	void init(int width, int height, int scale);
};

#endif //TALESOFCATVENTURE_ESCAPESCREEN_HPP
