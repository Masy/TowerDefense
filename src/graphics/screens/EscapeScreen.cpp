//
// Created by masy on 19.04.20.
//

#include <cedar/ScreenRegistry.hpp>
#include <cedar/FontRegistry.hpp>
#include <cedar/EngineThread.hpp>
#include <cedar/Cedar.hpp>
#include <cedar/TextureRegistry.hpp>
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
	std::shared_ptr<Font> font = FontRegistry::getFont("lazytown" + std::to_string(scale));
	if (!font)
		throw XException("Could not initialize escape screen. Font is not loaded!");

	std::shared_ptr<Texture> guiTexture = TextureRegistry::getTexture("gui");
	if (!guiTexture)
		throw XException("Could not initializes escape screen. GUI texture is not loaded!");

	float guiScale = static_cast<float>(scale);
	Vector4f cloudWhite(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
	Vector4f gray = Vector4f(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);

	float centerX = static_cast<float>(width) * 0.5f;
	float centerY = static_cast<float>(height) * 0.5f;
	float buttonWidth = 90.0f * guiScale;
	float buttonHeight = 24 * guiScale;
	float offset = buttonHeight + (4 * guiScale);
	unsigned int alignment = CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER;

	float pixelSize = 1.0f / 256.0f;
	Vector4f normalButtonDefaultUV(108.0f * pixelSize, 24.0f * pixelSize, 198.0f * pixelSize, 48.0f * pixelSize);
	Vector4f normalButtonHoveredUV(108.0f * pixelSize, 48.0f * pixelSize, 198.0f * pixelSize, 72.0f * pixelSize);
	Vector4f normalButtonPressedUV(108.0f * pixelSize, 72.0f * pixelSize, 198.0f * pixelSize, 96.0f * pixelSize);

	this->m_optionButton = new ImageButton(centerX, centerY - offset, 0, buttonWidth, buttonHeight,
										   guiTexture, normalButtonDefaultUV, normalButtonHoveredUV, normalButtonPressedUV,
										   "Options", font, cloudWhite, cloudWhite, gray, alignment);

	this->m_closeButton = new ImageButton(centerX, centerY, 1, buttonWidth, buttonHeight,
										  guiTexture, normalButtonDefaultUV, normalButtonHoveredUV, normalButtonPressedUV,
										  "Close", font, cloudWhite, cloudWhite, gray, alignment);
	this->m_closeButton->setInteractCallback(closeButtonInteractCallback);

	Vector4f redButtonDefaultUV(108.0f * pixelSize, 96.0f * pixelSize, 198.0f * pixelSize, 120.0f * pixelSize);
	Vector4f redButtonHoveredUV(108.0f * pixelSize, 120.0f * pixelSize, 198.0f * pixelSize, 144.0f * pixelSize);
	Vector4f redButtonPressedUV(108.0f * pixelSize, 144.0f * pixelSize, 198.0f * pixelSize, 168.0f * pixelSize);
	this->m_exitButton = new ImageButton(centerX, centerY + offset + (4 * guiScale), 2, buttonWidth, buttonHeight,
			guiTexture, redButtonDefaultUV, redButtonHoveredUV,redButtonPressedUV,
			"Exit", font, cloudWhite, cloudWhite, gray, alignment);
	this->m_exitButton->setInteractCallback(exitButtonInteractCallback);

	this->addElement(this->m_optionButton);
	this->addElement(this->m_closeButton);
	this->addElement(this->m_exitButton);
}
