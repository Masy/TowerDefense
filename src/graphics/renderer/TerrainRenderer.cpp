//
// Created by masy on 01.03.20.
//

#include "TerrainRenderer.h"
#include "glad/glad.h"
#include <fstream>
#include "cedar/ModelRegistry.h"

TerrainRenderer::TerrainRenderer()
{
	this->m_projectionMatrix = nullptr;
	this->m_viewMatrix = nullptr;
	this->m_terrainShader = nullptr;
	this->m_uniformLocations = nullptr;

}

TerrainRenderer::~TerrainRenderer() {
	delete this->m_terrainShader;
	delete this->m_terrainModel;
}

void TerrainRenderer::init(cedar::Matrix4f *projectionMatrix, cedar::Matrix4f *viewMatrix)
{
	this->m_projectionMatrix = projectionMatrix;
	this->m_viewMatrix = viewMatrix;

	std::string vertexSource = R"glsl(
#version 450

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;

out vec3 f_normal;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

void main()
{
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4(v_position, 1.0);
	f_normal = v_normal;
}

)glsl";

	std::string fragmentSource = R"glsl(
#version 450

const vec3 sunDir = normalize(vec3(-1.0, 1.0, -0.7));
const vec3 color = vec3(0.321568627, 0.458823529, 0.176470588);

layout (location = 0) out vec4 diffuseColor;

in vec3 f_normal;

void main()
{
	float brightness = max(0.3, dot(f_normal, sunDir));
	diffuseColor = vec4(color * brightness, 1.0);
}

)glsl";

	this->m_terrainShader = new cedar::ShaderProgram();
	this->m_terrainShader->createVertexShader(vertexSource);
	this->m_terrainShader->createFragmentShader(fragmentSource);
	this->m_terrainShader->link();

	const char *uniformNames[] = {"u_projectionMatrix", "u_viewMatrix"};
	this->m_uniformLocations = new int[2];
	this->m_terrainShader->createUniforms(2, uniformNames, this->m_uniformLocations);

	this->m_terrainModel = cedar::ModelRegistry::loadModel("terrain", "models/terrain.bin");
}

void TerrainRenderer::render() {
	this->m_terrainShader->bind();
	this->m_terrainShader->setUniform4x4f(this->m_uniformLocations[0], *this->m_projectionMatrix);
	this->m_terrainShader->setUniform4x4f(this->m_uniformLocations[1], *this->m_viewMatrix);

	if (this->m_terrainModel)
		this->m_terrainModel->render();
}
