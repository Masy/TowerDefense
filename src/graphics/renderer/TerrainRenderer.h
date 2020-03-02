//
// Created by masy on 01.03.20.
//

#ifndef TALESOFCATVENTURE_TERRAINRENDERER_H
#define TALESOFCATVENTURE_TERRAINRENDERER_H

#include <vector>

#include "cedar/ShaderProgram.h"
#include "cedar/Model.h"

/**
 * Renderer that renders the terrain.
 */
class TerrainRenderer
{
private:
	/**
	 * A pointer to the projection matrix of the window.
	 */
	cedar::Matrix4f *m_projectionMatrix;
	/**
	 * A pointer to the view matrix of the camera.
	 */
	cedar::Matrix4f *m_viewMatrix;
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
	~TerrainRenderer();

	/**
	 * Initializes the terrain renderer.
	 *
	 * @param projectionMatrix A pointer to the projection matrix of the window.
	 * @param viewMatrix A pointer to the view matrix of the camera.
	 */
	void init(cedar::Matrix4f *projectionMatrix, cedar::Matrix4f *viewMatrix);

	/**
	 * Renders the terrain.
	 */
	void render();
};

#endif //TALESOFCATVENTURE_TERRAINRENDERER_H
