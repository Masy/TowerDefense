//
// Created by masy on 01.03.20.
//

#ifndef TALESOFCATVENTURE_TERRAINRENDERER_H
#define TALESOFCATVENTURE_TERRAINRENDERER_H

#include <vector>

#include "cedar/ShaderProgram.h"
#include "cedar/Model.h"
#include "cedar/Renderer.h"

/**
 * Renderer that renders the terrain.
 */
class TerrainRenderer : public cedar::Renderer
{
private:
	/**
	 * A pointer to the projection matrix of the window.
	 */
	const cedar::Matrix4f *m_projectionMatrix;
	/**
	 * A pointer to the view matrix of the camera.
	 */
	const cedar::Matrix4f *m_viewMatrix;
	/**
	 * A pointer to the shader program of the terrain renderer.
	 */
	cedar::ShaderProgram *m_terrainShader;
	/**
	 * A pointer to the uniform locations of the shader.
	 */
	int *m_uniformLocations;

	/**
	 * A pointer to the model of the terrain.
	 */
	cedar::Model *m_terrainModel;

public:
	/**
	 * Creates a new terrain renderer.
	 */
	TerrainRenderer();

	/**
	 * Destroy the terrain renderer.
	 */
	~TerrainRenderer() override ;

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

#endif //TALESOFCATVENTURE_TERRAINRENDERER_H
