//
// Created by masy on 19.04.20.
//

#include <cedar/FontRegistry.hpp>
#include <cedar/OpenGLThread.hpp>
#include <cedar/EngineThread.hpp>
#include <cedar/Math.hpp>
#include <GameStates.h>
#include <cedar/ScreenRegistry.hpp>
#include "DebugScreen.hpp"

DebugScreen::DebugScreen()
	: Screen("debugScreen", 1)
{
	this->m_fpsLabel = nullptr;
	this->m_frameTimeLabel = nullptr;
	this->m_positionLabel = nullptr;
	this->m_rotationLabel = nullptr;
	this->m_stateLabel = nullptr;

	ScreenRegistry::registerScreen(this);
}

DebugScreen::~DebugScreen()
{
	delete this->m_fpsLabel;
	delete this->m_frameTimeLabel;
	delete this->m_positionLabel;
	delete this->m_rotationLabel;
	delete this->m_stateLabel;
}

void fpsLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	if (currentTick % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS()) == 0)
	{
		char fpsText[24];
		sprintf(fpsText, "FPS: %.0f", std::round(OpenGLThread::getInstance()->getFPS()));
		reinterpret_cast<Label*>(element)->setText(fpsText);
	}
}

void frameTimeLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	if (currentTick % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 4) == 0)
	{
		char frameTimeText[24];
		sprintf(frameTimeText, "FrameTime: %.2f", OpenGLThread::getInstance()->getLastFrameTime() * 1000.0);
		reinterpret_cast<Label*>(element)->setText(frameTimeText);
	}
}

void positionLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	if (currentTick % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 20) == 0)
	{
		Camera *camera = EngineThread::getInstance()->getCamera();
		if (camera)
		{
			const Vector3f pos = *camera->getPosition();
			char positionText[] = "Pos: 00000.000, 00000.000, 00000.000";
			sprintf(positionText, "Pos: %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
			reinterpret_cast<Label*>(element)->setText(positionText);
		}
	}
}

void rotationLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	if (currentTick % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 20) == 0)
	{
		Camera *camera = EngineThread::getInstance()->getCamera();
		if (camera)
		{
			const Vector3f rot = *camera->getRotationEuler();
			char rotationText[] = "Rot: 00.00°, 000.00°, 000.00°";
			sprintf(rotationText, "Rot: %.2f°, %.2f°, %.2f°", cedar::toDegrees(rot.x), cedar::toDegrees(rot.y), cedar::toDegrees(rot.z));
			reinterpret_cast<Label*>(element)->setText(rotationText);
		}
	}
}

void stateLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	unsigned int gameState = EngineThread::getInstance()->getGameState();

	switch (gameState)
	{
		case CEDAR_STATE_RUNNING:
			reinterpret_cast<Label*>(element)->setText("State: ingame");
			break;

		case TOC_STATE_MENU:
			reinterpret_cast<Label*>(element)->setText("State: menu");
			break;

		case TOC_STATE_PLACING:
			reinterpret_cast<Label*>(element)->setText("State: placing");
			break;

		default:
			reinterpret_cast<Label*>(element)->setText("State: unknown");
			break;
	}
}

void DebugScreen::init(const int width, const int height, const int scale) {

	Font *font_bold = FontRegistry::getFont("lazytown_bold" + std::to_string(scale));
	if (!font_bold)
		throw XException("Could not initialize debug screen. Font is not loaded!");

	float guiScale = static_cast<float>(scale);
	Vector4f cloudWhite(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
	float posX = 5.0f * guiScale;
	float offset = 12.0f * guiScale;
	float posY = std::round(static_cast<float>(height) * 0.5f) - (4 * offset);

	this->m_fpsLabel = new Label(posX, posY, 0, "FPS: 0", font_bold, cloudWhite);
	this->m_fpsLabel->setUpdateCallback(fpsLabelUpdateCallback);
	posY += offset;
	this->m_frameTimeLabel = new Label(posX, posY, 1, "FrameTime: 0.0", font_bold, cloudWhite);
	this->m_frameTimeLabel->setUpdateCallback(frameTimeLabelUpdateCallback);
	posY += offset;
	this->m_positionLabel = new Label(posX, posY, 2, "Pos: 0.0, 0.0, 0.0", font_bold, cloudWhite);
	this->m_positionLabel->setUpdateCallback(positionLabelUpdateCallback);
	posY += offset;
	this->m_rotationLabel = new Label(posX, posY, 3, "Rot: 0.0°, 0.0°, 0.0°", font_bold, cloudWhite);
	this->m_rotationLabel->setUpdateCallback(rotationLabelUpdateCallback);
	posY += offset;
	this->m_stateLabel = new Label(posX, posY, 4, "State: ingame", font_bold, cloudWhite);
	this->m_stateLabel->setUpdateCallback(stateLabelUpdateCallback);

	this->addElement(this->m_fpsLabel);
	this->addElement(this->m_frameTimeLabel);
	this->addElement(this->m_positionLabel);
	this->addElement(this->m_rotationLabel);
	this->addElement(this->m_stateLabel);
}
