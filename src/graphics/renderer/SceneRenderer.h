//
// Created by masy on 01.03.20.
//

#ifndef TALESOFCATVENTURE_SCENERENDERER_H
#define TALESOFCATVENTURE_SCENERENDERER_H

#include <vector>

#include "cedar/ShaderProgram.hpp"
#include "cedar/Model.hpp"
#include "cedar/Renderer.hpp"
#include "cedar/Texture2D.hpp"
#include "TDMap.h"

/**
 * Renderer that renders the terrain.
 */
class SceneRenderer : public cedar::Renderer
{
private:
	/**
	 * A pointer to the projection view matrix of the game.
	 */
	const cedar::Matrix4f *m_projectionViewMatrix;
	/**
	 * A pointer to the shader program of the terrain renderer.
	 */
	cedar::ShaderProgram *m_sceneShader;
	/**
	 * A pointer to the uniform locations of the shader.
	 */
	int *m_uniformLocations;

	/**
	 * A pointer to current map.
	 */
	TDMap *m_currentMap;

	/**
	 * A pointer to the texture of the terrain.
	 */
	cedar::Texture2D *m_terrainTexture;

	/**
	 * Creates a new terrain renderer.
	 */
	SceneRenderer();

public:
	/**
	 * Gets the singleton instance of the scene renderer.
	 *
	 * @return A pointer to the scene renderer instance.
	 */
	static SceneRenderer *getInstance();

	/**
	 * Destroy the terrain renderer.
	 */
	~SceneRenderer() override;

	/**
	 * Initializes the terrain renderer.
	 */
	void init() override;

	/**
	 * Method which is called when the window is resized.
	 */
	void onResize() override;

	/**
	 * Renders the terrain.
	 */
	void render(unsigned long currentTime, unsigned long tickCount) override;
};

#endif //TALESOFCATVENTURE_SCENERENDERER_H
