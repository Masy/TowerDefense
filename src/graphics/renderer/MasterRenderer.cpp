//
// Created by masy on 04.02.20.
//

#include "MasterRenderer.h"
#include "EngineThread.h"
#include "cedar/Math.h"
#include "ToC.h"

MasterRenderer::MasterRenderer(cedar::Window *window)
{
	this->m_window = window;
	this->m_projectionMatrix = new cedar::Matrix4f();
	this->m_orthoProjMatrix = new cedar::Matrix4f();
	this->m_viewMatrix = new cedar::Matrix4f();
	this->m_guiRenderer = new cedar::GuiRenderer();
	this->m_terrainRenderer = new TerrainRenderer();
}

void MasterRenderer::init()
{
	this->resize();

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.02f, 0.02f, 0.02f, 1.0f);

	this->m_guiRenderer->init(4096, this->m_orthoProjMatrix);
	this->m_terrainRenderer->init(this->m_projectionMatrix, this->m_viewMatrix);
}

void MasterRenderer::resize()
{
	this->m_projectionMatrix->perspective(
			static_cast<float>(this->m_window->getRatio()),
			cedar::math::toRadians(ToC::getInstance()->m_config->m_graphicsConfig.m_fov),
			1E-2f,
			4096.0f);
	this->m_projectionMatrix->scale(1.0f, 1.0f, 1.0f);

	this->m_orthoProjMatrix->orthographic(0.0f, static_cast<float>(this->m_window->getWidth()), static_cast<float>(this->m_window->getHeight()), 0.0f, 1E-6f, 4096);
}

void MasterRenderer::render(unsigned long currentTime, unsigned long currentTick)
{
	Camera *camera = EngineThread::getInstance()->getCamera();
	cedar::Vector3f lerpedPosition;
	cedar::Quaternionf lerpedRotation;
	camera->getLerpedPosition(currentTime, &lerpedPosition);
	camera->getSlerpedRotation(currentTime, &lerpedRotation);
	this->m_viewMatrix->translation(0, 0, -(camera->getLerpedZoomLevel(currentTime)));
	this->m_viewMatrix->rotate(&lerpedRotation);
	this->m_viewMatrix->translate(-lerpedPosition.x, -lerpedPosition.y, -lerpedPosition.z);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDisable(GL_BLEND);
//	glPolygonMode(GL_FRONT, GL_LINE);
	this->m_terrainRenderer->render();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	cedar::Vector4f color1 = {1.0f, 0.0f, 0.5f, 1.0f};
//	cedar::Vector4f color2 = {0.0f, 0.5f, 0.5f, 0.5f};
//	this->m_guiRenderer->beginBatch();
//	this->m_guiRenderer->drawRect(10.0f, 10.0f, 1.0f, 50.0f, 20.0f, &color1);
//	this->m_guiRenderer->drawRect(10.0f, 60.0f, 1.0f, 50.0f, 20.0f, &color1);
//	this->m_guiRenderer->drawRect(20.0f, 20.0f, 0.0f, 50.0f, 20.0f, &color2);
//	this->m_guiRenderer->drawRect(10.0f, 120.0f, 0.0f, 50.0f, 20.0f, &color2);
//	this->m_guiRenderer->drawRect(10.0f, 150.0f, 0.0f, 50.0f, 20.0f, &color2);
//	this->m_guiRenderer->endBatch();
//	this->m_guiRenderer->flush();
}