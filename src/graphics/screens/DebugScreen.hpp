//
// Created by masy on 19.04.20.
//

#ifndef TALESOFCATVENTURE_DEBUGSCREEN_HPP
#define TALESOFCATVENTURE_DEBUGSCREEN_HPP

#include "cedar/Screen.hpp"
#include "cedar/Label.hpp"

using namespace cedar;

/**
 * Class representing the debug screen.
 */
class DebugScreen : public Screen
{
private:
	/**
	 * A pointer to the fps label.
	 */
	Label *m_fpsLabel;
	/**
	 * A pointer to the frame time label.
	 */
	Label *m_frameTimeLabel;
	/**
	 * A pointer to the position label.
	 */
	Label *m_positionLabel;
	/**
	 * A pointer to the rotation label.
	 */
	Label *m_rotationLabel;
	/**
	 * A pointer to the state label.
	 */
	Label *m_stateLabel;

public:
	/**
	 * Creates a new debug screen.
	 */
	DebugScreen();

	/**
	 * Deletes the debug screen.
	 */
	~DebugScreen();

	/**
	 * Initializes the debug screen.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param guiScale The scale of the gui.
	 */
	void init(int width, int height, int guiScale);
};

#endif //TALESOFCATVENTURE_DEBUGSCREEN_HPP
