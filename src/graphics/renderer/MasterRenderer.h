//
// Created by masy on 26.01.20.
//

#ifndef TALESOFCATVENTURE_MASTERRENDERER_H
#define TALESOFCATVENTURE_MASTERRENDERER_H

#include "cedar/Window.h"
#include "cedar/Matrix4f.h"
#include "cedar/ShaderProgram.h"
#include "cedar/GuiRenderer.h"
#include "TerrainRenderer.h"

/**
 * Class representing the master renderer which calls all other renderers.
 */
class MasterRenderer
{
private:
	/**
	 * A pointer to the window of the game.
	 */
	cedar::Window *m_window;
	/**
	 * A pointer to the perspective projection matrix of the window.
	 */
	cedar::Matrix4f *m_projectionMatrix;
	/**
	 * A pointer to the orthographic projection matrix of the window.
	 */
	cedar::Matrix4f *m_orthoProjMatrix;
	/**
	 * A pointer to the view matrix of the camera.
	 */
	cedar::Matrix4f *m_viewMatrix;
	/**
	 * A pointer to the gui renderer.
	 */
	cedar::GuiRenderer *m_guiRenderer;

public:
	/**
	 * A pointer to the terrain renderer.
	 */
	TerrainRenderer *m_terrainRenderer;

	/**
	 * Constructs a new master renderer.
	 */
	explicit MasterRenderer(cedar::Window *window);
	/**
	 * Initializes the master renderer and all other renderers.
	 */
	void init();

	/**
	 * Updates the projection matrices to the current size of the window.
	 */
	void resize();
	/**
	 * Renders a frame.
	 *
	 * @param currentTime The current time in microseconds.
	 * @param currentTick The current tick count.
	 */
	void render(unsigned long currentTime, unsigned long currentTick);
};

#endif //TALESOFCATVENTURE_MASTERRENDERER_H
