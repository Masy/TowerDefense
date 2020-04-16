//
// Created by masy on 11.03.20.
//

#include <cedar/MasterRenderer.hpp>
#include <cedar/OpenGLThread.hpp>
#include <cedar/Cedar.hpp>
#include <cedar/EngineThread.hpp>
#include "DebugRenderer.h"
#include "glad/glad.h"
#include "cedar/ModelRegistry.hpp"
#include "TDMap.h"

DebugRenderer::DebugRenderer()
{
	this->m_projectionViewMatrix = nullptr;
	this->m_transformationMatrix = new cedar::Matrix4f();
	this->m_shader = nullptr;
	this->m_uniformLocations = nullptr;
	this->m_mouseRayModel = nullptr;
}

DebugRenderer::~DebugRenderer()
{
	delete this->m_transformationMatrix;
	delete this->m_shader;
	delete[] this->m_uniformLocations;
	cedar::ModelRegistry::cleanup("mouseRay");
}

void DebugRenderer::init() {
	cedar::MasterRenderer  *masterRenderer = cedar::OpenGLThread::getInstance()->getMasterRenderer();
	this->m_projectionViewMatrix = masterRenderer->getProjectionViewMatrix();

	unsigned char bitMask;
	this->m_mouseRayModel = cedar::ModelRegistry::loadBMFModel("intersection", "models/intersection.bmf", &bitMask);
	glBindVertexArray(this->m_mouseRayModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, this->m_mouseRayModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	cedar::ModelRegistry::registerModel("mouseRay", this->m_mouseRayModel);

	std::string vertexShaderSource = R"glsl(
#version 450

layout (location = 0) in vec3 v_position;

uniform mat4 u_projectionViewMatrix;
uniform mat4 u_transformationMatrix;

void main()
{
	gl_Position = u_projectionViewMatrix * u_transformationMatrix * vec4(v_position, 1.0);
}

)glsl";

	std::string fragmentShaderSource = R"glsl(
#version 450

layout (location = 0) out vec4 diffuseColor;

uniform vec3 u_color;

void main()
{
	diffuseColor = vec4(u_color, 1.0);
}

)glsl";

	this->m_shader = new cedar::ShaderProgram();
	this->m_shader->createVertexShader(vertexShaderSource);
	this->m_shader->createFragmentShader(fragmentShaderSource);
	this->m_shader->link();

	const char *uniformNames[] = {"u_projectionViewMatrix", "u_transformationMatrix", "u_color"};
	this->m_uniformLocations = new int[3];
	this->m_shader->createUniforms(3, uniformNames, this->m_uniformLocations);
}

void DebugRenderer::onResize() {

}

void DebugRenderer::render(const unsigned long currentTime, const unsigned long tickCount)
{
	if (this->m_mouseRayModel)
	{
		cedar::Vector3f origin;
		cedar::Vector3f rayDir;

		cedar::OpenGLThread::getInstance()->getMasterRenderer()->getMouseRay(&origin, &rayDir);

		// Calculate where the ray hits y = 0
		float r = - (origin.y / rayDir.y);

		cedar::Vector3f planeIntersection = origin + (rayDir * r);

		this->m_transformationMatrix->translation(&planeIntersection);

		Vector3f color(0.0f, 0.0f, 1.0f);
		TDMap *map = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
		if (map)
		{
			Vector2f intersection(planeIntersection.x, planeIntersection.z);
			if (!map->isPositionValid(intersection, 1.0f))
				color = Vector3f(1.0f, 0.0f, 0.0f);
		}

		this->m_shader->bind();
		this->m_shader->setUniform4x4f(this->m_uniformLocations[0], *this->m_projectionViewMatrix);
		this->m_shader->setUniform4x4f(this->m_uniformLocations[1], *this->m_transformationMatrix);
		this->m_shader->setUniform3f(this->m_uniformLocations[2], color);
		this->m_mouseRayModel->render();
	}
}
