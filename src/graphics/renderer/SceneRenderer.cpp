//
// Created by masy on 01.03.20.
//

#include <cedar/EngineThread.hpp>
#include "SceneRenderer.h"
#include "glad/glad.h"
#include "cedar/MasterRenderer.hpp"
#include "cedar/OpenGLThread.hpp"
#include "cedar/ModelRegistry.hpp"

SceneRenderer::SceneRenderer()
{
	this->m_projectionViewMatrix = nullptr;
	this->m_sceneShader = nullptr;
	this->m_uniformLocations = nullptr;
	this->m_currentMap = nullptr;
	this->m_terrainTexture = nullptr;
}

SceneRenderer::~SceneRenderer() {
	delete this->m_sceneShader;
}

SceneRenderer *SceneRenderer::getInstance() {
	static SceneRenderer *instance = new SceneRenderer();
	return instance;
}

void SceneRenderer::init()
{
	cedar::MasterRenderer  *masterRenderer = cedar::OpenGLThread::getInstance()->getMasterRenderer();
	this->m_projectionViewMatrix = masterRenderer->getProjectionViewMatrix();

	std::string vertexSource = R"glsl(
#version 450

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uvs;
layout (location = 2) in vec3 v_normal;

out vec3 f_normal;
out vec3 f_color;

uniform mat4 u_projectionViewMatrix;
uniform mat4 u_transformationMatrix;

uniform sampler2D u_sampler;

void main()
{
	gl_Position = u_projectionViewMatrix * u_transformationMatrix * vec4(v_position, 1.0);
	f_normal = v_normal;
	f_color = texture(u_sampler, v_uvs).rgb;
}

)glsl";

	std::string fragmentSource = R"glsl(
#version 450

const vec3 sunDir = normalize(vec3(0.4, 1.0, 0.6));

layout (location = 0) out vec4 diffuseColor;

in vec3 f_normal;
in vec3 f_color;

uniform vec3 u_tint;

void main()
{
	float brightness = max(0.3, dot(f_normal, sunDir));
	diffuseColor = vec4(f_color * u_tint * brightness, 1.0);
}

)glsl";

	this->m_sceneShader = new cedar::ShaderProgram();
	this->m_sceneShader->createVertexShader(vertexSource);
	this->m_sceneShader->createFragmentShader(fragmentSource);
	this->m_sceneShader->link();

	const char *uniformNames[] = {"u_projectionViewMatrix", "u_transformationMatrix", "u_sampler", "u_tint"};
	this->m_uniformLocations = new int[4];
	this->m_sceneShader->createUniforms(4, uniformNames, this->m_uniformLocations);

	this->m_currentMap = reinterpret_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
	this->m_terrainTexture = new cedar::Texture2D(4, 4, CEDAR_RGB8, CEDAR_TEXTURE_2D);
	unsigned char data[] = {
			0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF,

			0xA7, 0x75, 0x24,
			0xAF, 0xC0, 0xC0,
			0xC6, 0xB4, 0x46,
			0xFF, 0xFF, 0xFF,

			0xFF, 0xD3, 0xEF,
			0xFF, 0xFF, 0xFF,
			0x3B, 0x42, 0x47,
			0x82, 0x8F, 0x98,

			0x76, 0xB2, 0x31,
			0xD3, 0xB6, 0x65,
			0x6B, 0x63, 0x56,
			0x38, 0x2C, 0x24,
	};
	this->m_terrainTexture->init(CEDAR_RGB, CEDAR_UNSIGNED_BYTE, data);
	this->m_terrainTexture->setParameteri(CEDAR_TEXTURE_MIN_FILTER, CEDAR_NEAREST);
	this->m_terrainTexture->setParameteri(CEDAR_TEXTURE_MAG_FILTER, CEDAR_NEAREST);
	this->m_terrainTexture->setParameteri(CEDAR_TEXTURE_WRAP_S, CEDAR_CLAMP_TO_EDGE);
	this->m_terrainTexture->setParameteri(CEDAR_TEXTURE_WRAP_T, CEDAR_CLAMP_TO_EDGE);
}

void SceneRenderer::onResize() {

}

void SceneRenderer::render(unsigned long currentTime, unsigned long tickCount) {

	if (this->m_currentMap)
	{
		glDisable(GL_BLEND);
		glBindTextureUnit(0, this->m_terrainTexture->getId());
		this->m_sceneShader->bind();
		this->m_sceneShader->setUniform4x4f(this->m_uniformLocations[0], *this->m_projectionViewMatrix);
		this->m_sceneShader->setUniform1i(this->m_uniformLocations[1], 0);

		this->m_currentMap->render(currentTime, tickCount, this->m_sceneShader);

		glEnable(GL_BLEND);
	}
}
