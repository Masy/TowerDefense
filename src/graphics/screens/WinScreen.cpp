//
// Created by masy on 27.04.20.
//

#include "WinScreen.hpp"
#include "cedar/ScreenRegistry.hpp"
#include "cedar/TextureRegistry.hpp"
#include "cedar/FontRegistry.hpp"
#include "cedar/EngineThread.hpp"
#include "TDMap.h"

WinScreen::WinScreen()
		: Screen("winScreen", 3)
{
	this->m_winLabel = nullptr;
	this->m_playAgainButton = nullptr;

	ScreenRegistry::registerScreen(this);
}

WinScreen::~WinScreen()
{
	delete this->m_winLabel;
	delete this->m_playAgainButton;
}

void playAgainButtonInteractHandler(Element *element)
{
	TDMap *map = dynamic_cast<TDMap*>(EngineThread::getInstance()->getLoadedScene());

	map->restart();
	ScreenRegistry::getScreen("ingameScreen")->setVisibility(true);
	ScreenRegistry::getScreen("winScreen")->setVisibility(false);
}

void WinScreen::init(const int width, const int height, const int scale)
{
	std::shared_ptr<Texture> guiTexture = TextureRegistry::getTexture("gui");
	if (!guiTexture)
		throw XException("Could not initializes win screen. GUI texture is not loaded!");

	std::shared_ptr<Font> font = FontRegistry::getFont("lazytown" + std::to_string(scale));
	if (!font)
		throw XException("Could not initialize win screen. Font is not loaded!");

	std::shared_ptr<Font> font_bold = FontRegistry::getFont("lazytown_bold" + std::to_string(scale));
	if (!font_bold)
		throw XException("Could not initialize win screen. Bold font is not loaded!");

	float guiScale = static_cast<float>(scale);
	Vector4f cloudWhite(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
	Vector4f gray = Vector4f(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);
	Vector4f green(0x52 / 255.0f, 0xB3 / 255.0f, 0x47 / 255.0f, 1.0f);

	float centerX = static_cast<float>(width) * 0.5f;
	float centerY = static_cast<float>(height) * 0.5f;
	float buttonWidth = 90.0f * guiScale;
	float buttonHeight = 24 * guiScale;
	float pixelSize = 1.0f / 256.0f;

	Vector4f buttonDefaultUV(108.0f * pixelSize, 24.0f * pixelSize, 198.0f * pixelSize, 48.0f * pixelSize);
	Vector4f buttonHoveredUV(108.0f * pixelSize, 48.0f * pixelSize, 198.0f * pixelSize, 72.0f * pixelSize);
	Vector4f buttonPressedUV(108.0f * pixelSize, 72.0f * pixelSize, 198.0f * pixelSize, 96.0f * pixelSize);
	this->m_playAgainButton = new ImageButton(centerX, centerY, 0, buttonWidth, buttonHeight,
											guiTexture, buttonDefaultUV, buttonHoveredUV, buttonPressedUV,
											"Play Again", font, cloudWhite, cloudWhite, gray,
											CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);
	this->m_playAgainButton->setDefaultCaptionOffset(- 1.0f - (2.0f * guiScale));
	this->m_playAgainButton->setHoveredCaptionOffset(- 1.0f - (2.0f * guiScale));
	this->m_playAgainButton->setPressedCaptionOffset(- 1.0f);
	this->m_playAgainButton->setInteractCallback(playAgainButtonInteractHandler);

	this->m_winLabel = new Label(centerX, centerY - buttonHeight - (static_cast<float>(font_bold->getSize()) * 0.5f), 1, "- YOU WON -", font_bold, green, CEDAR_ALIGNMENT_MIDDLE | CEDAR_ALIGNMENT_CENTER);

	this->addElement(this->m_winLabel);
	this->addElement(this->m_playAgainButton);
}

