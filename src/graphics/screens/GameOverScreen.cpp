//
// Created by masy on 26.04.20.
//

#include <cedar/TextureRegistry.hpp>
#include <cedar/FontRegistry.hpp>
#include <cmath>
#include <cedar/EngineThread.hpp>
#include <TDMap.h>
#include "GameOverScreen.hpp"
#include "cedar/ScreenRegistry.hpp"

GameOverScreen::GameOverScreen()
		: Screen("gameOverScreen", 3)
{
	this->m_gameOverLabel = nullptr;
	this->m_restartButton = nullptr;

	ScreenRegistry::registerScreen(this);
}

GameOverScreen::~GameOverScreen()
{
	delete this->m_gameOverLabel;
	delete this->m_restartButton;
}

void restartButtonInteractHandler(Element *element)
{
	TDMap *map = dynamic_cast<TDMap*>(EngineThread::getInstance()->getLoadedScene());

	map->restart();
	ScreenRegistry::getScreen("ingameScreen")->setVisibility(true);
	ScreenRegistry::getScreen("gameOverScreen")->setVisibility(false);
}

void GameOverScreen::init(const int width, const int height, const int scale)
{
	std::shared_ptr<Texture> guiTexture = TextureRegistry::getTexture("gui");
	if (!guiTexture)
		throw XException("Could not initializes game over screen. GUI texture is not loaded!");

	std::shared_ptr<Font> font = FontRegistry::getFont("lazytown" + std::to_string(scale));
	if (!font)
		throw XException("Could not initialize game over screen. Font is not loaded!");

	std::shared_ptr<Font> font_bold = FontRegistry::getFont("lazytown_bold" + std::to_string(scale));
	if (!font_bold)
		throw XException("Could not initialize game over screen. Bold font is not loaded!");

	float guiScale = static_cast<float>(scale);
	Vector4f cloudWhite(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
	Vector4f gray = Vector4f(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);
	Vector4f red(0xCC / 255.0f, 0x49 / 255.0f, 0x3D / 255.0f, 1.0f);

	float centerX = static_cast<float>(width) * 0.5f;
	float centerY = static_cast<float>(height) * 0.5f;
	float buttonWidth = 90.0f * guiScale;
	float buttonHeight = 24 * guiScale;
	float pixelSize = 1.0f / 256.0f;

	Vector4f buttonDefaultUV(108.0f * pixelSize, 24.0f * pixelSize, 198.0f * pixelSize, 48.0f * pixelSize);
	Vector4f buttonHoveredUV(108.0f * pixelSize, 48.0f * pixelSize, 198.0f * pixelSize, 72.0f * pixelSize);
	Vector4f buttonPressedUV(108.0f * pixelSize, 72.0f * pixelSize, 198.0f * pixelSize, 96.0f * pixelSize);
	this->m_restartButton = new ImageButton(centerX, centerY, 0, buttonWidth, buttonHeight,
											guiTexture, buttonDefaultUV, buttonHoveredUV, buttonPressedUV,
											"Restart", font, cloudWhite, cloudWhite, gray,
											CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);
	this->m_restartButton->setDefaultCaptionOffset(- 1.0f - (2.0f * guiScale));
	this->m_restartButton->setHoveredCaptionOffset(- 1.0f - (2.0f * guiScale));
	this->m_restartButton->setPressedCaptionOffset(- 1.0f);
	this->m_restartButton->setInteractCallback(restartButtonInteractHandler);

	this->m_gameOverLabel = new Label(centerX, centerY - buttonHeight - (static_cast<float>(font_bold->getSize()) * 0.5f), 1, "- GAME OVER -", font_bold, red, CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);

	this->addElement(this->m_gameOverLabel);
	this->addElement(this->m_restartButton);
}


