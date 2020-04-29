//
// Created by masy on 27.04.20.
//

#ifndef GUARDIAN_WINSCREEN_HPP
#define GUARDIAN_WINSCREEN_HPP

#include "cedar/Screen.hpp"
#include "cedar/Label.hpp"
#include "cedar/ImageButton.hpp"

using namespace cedar;

/**
 * Class representing the win screen.
 */
class WinScreen : public Screen
{
private:
	/**
	 * A pointer to the win text label.
	 */
	Label *m_winLabel;
	/**
	 * A pointer to the play again button.
	 */
	ImageButton *m_playAgainButton;

public:
	/**
	 * Creates a new win screen.
	 */
	WinScreen();

	/**
	 * Deletes the win screen.
	 */
	~WinScreen();

	/**
	 * Initializes the win screen.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param scale The scale of the gui.
	 */
	void init(int width, int height, int scale);
};

#endif //GUARDIAN_WINSCREEN_HPP
