//
// Created by masy on 11.03.20.
//

#ifndef GUARDIAN_DEBUGRENDERER_H
#define GUARDIAN_DEBUGRENDERER_H

#include "cedar/Renderer.hpp"
#include "cedar/ShaderProgram.hpp"
#include "cedar/Model.hpp"

using namespace cedar;

/**
 * CLass for rendering debug information.
 */
class DebugRenderer : public cedar::Renderer
{
private:
	/**
	 * A pointer to the projection matrix of the window.
	 */
	const Matrix4f *m_projectionViewMatrix;
	/**
	 * A pointer to a transformation matrix.
	 */
	Matrix4f *m_transformationMatrix;
	/**
	 * A pointer to the shader used to render the debug information.
	 */
	ShaderProgram *m_shader;
	/**
	 * A pointer to the array of uniform locations.
	 */
	int *m_uniformLocations;
	/**
	 * A pointer to the mouse ray model.
	 */
	Model *m_mouseRayModel;

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
