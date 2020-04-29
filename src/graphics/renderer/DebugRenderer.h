//
// Created by masy on 11.03.20.
//

#ifndef GUARDIAN_DEBUGRENDERER_H
#define GUARDIAN_DEBUGRENDERER_H

#include "cedar/Renderer.hpp"
#include "cedar/ShaderProgram.hpp"
#include "cedar/Model.hpp"

class DebugRenderer : public cedar::Renderer
{
private:
	const cedar::Matrix4f *m_projectionViewMatrix;
	cedar::Matrix4f *m_transformationMatrix;
	cedar::ShaderProgram *m_shader;
	int *m_uniformLocations;
	cedar::Model *m_mouseRayModel;

public:
	/**
	 * Creates a new terrain renderer.
	 */
	DebugRenderer();

	/**
	 * Destroy the terrain renderer.
	 */
	~DebugRenderer() override;

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

#endif //GUARDIAN_DEBUGRENDERER_H
