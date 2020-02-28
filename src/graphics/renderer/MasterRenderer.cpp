//
// Created by masy on 04.02.20.
//

#include "MasterRenderer.h"
#include "EngineThread.h"
#include "cedar/Math.h"
#include "ToC.h"
#include "OpenGLThread.h"

MasterRenderer::MasterRenderer(cedar::Window *window)
{
	this->m_window = window;
	this->m_projectionMatrix = new cedar::Matrix4f();
	this->m_orthoProjMatrix = new cedar::Matrix4f();
	this->m_viewMatrix = new cedar::Matrix4f();
	this->m_guiRenderer = new cedar::GuiRenderer();
}

void MasterRenderer::init()
{
	this->resize();
	this->m_guiRenderer->init(4096, this->m_orthoProjMatrix);

	//TEMP
	glGenVertexArrays(1, &this->m_vaoId);
	glBindVertexArray(this->m_vaoId);

	glGenBuffers(1, &this->m_vboId);

	float data[] = {
			// TOP
			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

			// BOTTOM
			1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

			// NORTH
			1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,

			// EAST
			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

			// SOUTH
			-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,

			// WEST
			-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 7, nullptr); // position
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 7, (const void*) 12); // color

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string vertexShader = R"glsl(
#version 450

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec4 v_color;

out vec4 f_color;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

void main()
{
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4(v_position, 1.0);
	f_color = v_color;
}

)glsl";

	std::string fragmentShader = R"glsl(
#version 450

layout (location = 0) out vec4 diffuseColor;

in vec4 f_color;

void main()
{
	diffuseColor = f_color;
}

)glsl";

	this->m_shader = new cedar::ShaderProgram();
	this->m_shader->createVertexShader(vertexShader);
	this->m_shader->createFragmentShader(fragmentShader);
	this->m_shader->link();

	const char *uniformNames[] = {"u_projectionMatrix", "u_viewMatrix"};
	this->m_defaultUniformLocations = new int[2];
	this->m_shader->createUniforms(2, uniformNames, this->m_defaultUniformLocations);
	// END TEMP

	glEnable(GL_MULTISAMPLE);
	glClearColor(0.02f, 0.02f, 0.02f, 1.0f);
}

void MasterRenderer::resize()
{
	this->m_projectionMatrix->perspective(
			static_cast<float>(this->m_window->getRatio()),
			cedar::math::toRadians(ToC::getInstance()->m_config->m_graphicsConfig.m_fov),
			1E-6f,
			4096.0f);

	this->m_orthoProjMatrix->orthographic(0.0f, static_cast<float>(this->m_window->getWidth()), static_cast<float>(this->m_window->getHeight()), 0.0f, 1E-6f, 4096);
}

void MasterRenderer::render(unsigned long currentTime, unsigned long currentTick)
{
	Camera *camera = EngineThread::getInstance()->getCamera();
	cedar::Vector3f lerpedPosition(0.0f);
	cedar::Vector3f lerpedRotation;
	camera->getLerpedPosition(currentTime, &lerpedPosition);
	camera->getLerpedRotation(currentTime, &lerpedRotation);
	this->m_viewMatrix->translation(0, 0, -(camera->getLerpedZoomLevel(currentTime)));
	this->m_viewMatrix->rotate(&lerpedRotation);
	this->m_viewMatrix->translate(-lerpedPosition.x, -lerpedPosition.y, -lerpedPosition.z);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->m_shader->bind();
	this->m_shader->setUniform4x4f(this->m_defaultUniformLocations[0], *this->m_projectionMatrix);
	this->m_shader->setUniform4x4f(this->m_defaultUniformLocations[1], *this->m_viewMatrix);

	glBindVertexArray(this->m_vaoId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	this->m_shader->unbind();

	const cedar::Logger *logger = OpenGLThread::getInstance()->getLogger();

	cedar::Vector4f color1 = {1.0f, 0.0f, 0.5f, 1.0f};
	cedar::Vector4f color2 = {0.0f, 0.5f, 0.5f, 0.5f};
	this->m_guiRenderer->beginBatch();
	this->m_guiRenderer->drawRect(10.0f, 10.0f, 1.0f, 50.0f, 20.0f, &color1);
	this->m_guiRenderer->drawRect(10.0f, 60.0f, 1.0f, 50.0f, 20.0f, &color1);
	this->m_guiRenderer->drawRect(20.0f, 20.0f, 0.0f, 50.0f, 20.0f, &color2);
	this->m_guiRenderer->drawRect(10.0f, 120.0f, 0.0f, 50.0f, 20.0f, &color2);
	this->m_guiRenderer->drawRect(10.0f, 150.0f, 0.0f, 50.0f, 20.0f, &color2);
	this->m_guiRenderer->endBatch();
	this->m_guiRenderer->flush();
}