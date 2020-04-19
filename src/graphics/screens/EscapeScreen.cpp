//
// Created by masy on 19.04.20.
//

#include <cedar/ScreenRegistry.hpp>
#include <cedar/FontRegistry.hpp>
#include <cedar/EngineThread.hpp>
#include <cedar/Cedar.hpp>
#include "EscapeScreen.hpp"

EscapeScreen::EscapeScreen()
		: Screen("escapeScreen", 2)
{
	this->m_optionButton = nullptr;
	this->m_closeButton = nullptr;
	this->m_exitButton = nullptr;

	ScreenRegistry::registerScreen(this);
}

EscapeScreen::~EscapeScreen()
{
	delete this->m_optionButton;
	delete this->m_closeButton;
	delete this->m_exitButton;
}

void closeButtonInteractCallback(const Element *element)
{
	EngineThread::getInstance()->setGameState(CEDAR_STATE_RUNNING);
	ScreenRegistry::getScreen("escapeScreen")->setVisibility(false);
}

void exitButtonInteractCallback(const Element *element)
{
	Cedar::getInstance()->stop();
}

void EscapeScreen::init(const int width, const int height, const int scale)
{

	Font *font_bold = FontRegistry::getFont("lazytown_bold" + std::to_string(scale));
	if (!font_bold)
		throw XException("Could not initialize escape screen. Font is not loaded!");

	float guiScale = static_cast<float>(scale);
	Vector4f cloudWhite(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
	Vector4f gray = Vector4f(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);
	Vector4f background(0x95 / 255.0f, 0xA5 / 255.0f, 0xA5 / 255.0f, 1.0f);
	Vector4f hoverBlue(0x34 / 255.0f, 0x98 / 255.0f, 0xDB / 255.0f, 1.0f);
	Vector4f pressBlue(0x29 / 255.0f, 0x80 / 255.0f, 0xB9 / 255.0f, 1.0f);
	Vector4f hoverRed(0xE7 / 255.0f, 0x4C / 255.0f, 0x3C / 255.0f, 1.0f);
	Vector4f pressRed(0xC0 / 255.0f, 0x39 / 255.0f, 0x2B / 255.0f, 1.0f);

	float centerX = static_cast<float>(width) * 0.5f;
	float centerY = static_cast<float>(height) * 0.5f;
	float buttonWidth = 90.0f * guiScale;
	float buttonHeight = 21 * guiScale;
	float offset = buttonHeight + (8 * guiScale);
	unsigned int alignment = CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER;

	this->m_optionButton = new Button(centerX, centerY - offset, 0, buttonWidth, buttonHeight, "Options", font_bold, cloudWhite, alignment);
	this->m_optionButton->setBackgroundColor(background);
	this->m_optionButton->setHoveredBackgroundColor(hoverBlue);
	this->m_optionButton->setPressedBackgroundColor(pressBlue);
	this->m_optionButton->setPressedTextColor(gray);

	this->m_closeButton = new Button(centerX, centerY, 1, buttonWidth, buttonHeight, "Close", font_bold, cloudWhite, alignment);
	this->m_closeButton->setBackgroundColor(background);
	this->m_closeButton->setHoveredBackgroundColor(hoverBlue);
	this->m_closeButton->setPressedBackgroundColor(pressBlue);
	this->m_closeButton->setPressedTextColor(gray);
	this->m_closeButton->setInteractCallback(closeButtonInteractCallback);

	this->m_exitButton = new Button(centerX, centerY + offset + buttonHeight, 2, buttonWidth, buttonHeight, "Exit", font_bold, cloudWhite, alignment);
	this->m_exitButton->setBackgroundColor(background);
	this->m_exitButton->setHoveredBackgroundColor(hoverRed);
	this->m_exitButton->setPressedBackgroundColor(pressRed);
	this->m_exitButton->setPressedTextColor(gray);
	this->m_exitButton->setInteractCallback(exitButtonInteractCallback);

	this->addElement(this->m_optionButton);
	this->addElement(this->m_closeButton);
	this->addElement(this->m_exitButton);
}
