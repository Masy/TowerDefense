//
// Created by masy on 19.04.20.
//

#include <cedar/ScreenRegistry.hpp>
#include <cedar/TextureRegistry.hpp>
#include <cedar/FontRegistry.hpp>
#include <cedar/EngineThread.hpp>
#include "TDMap.h"
#include "IngameScreen.hpp"

IngameScreen::IngameScreen()
		: Screen("ingameScreen", 0)
{
	this->m_healthIcon = nullptr;
	this->m_coinIcon = nullptr;
	this->m_healthLabel = nullptr;
	this->m_coinLabel = nullptr;
	this->m_roundLabel = nullptr;

	ScreenRegistry::registerScreen(this);
}

IngameScreen::~IngameScreen()
{
	delete this->m_healthIcon;
	delete this->m_coinIcon;
	delete this->m_healthLabel;
	delete this->m_coinLabel;
	delete this->m_roundLabel;
}

void healthLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	TDMap *map = dynamic_cast<TDMap *>(cedar::EngineThread::getInstance()->getLoadedScene());
	char healthText[] = "000";
	sprintf(healthText, "%d", map->getPlayer()->getHealth());
	reinterpret_cast<Label *>(element)->setText(healthText);
}

void coinLabelUpdateCallback(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	TDMap *map = dynamic_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
	char coinText[] = "000000";
	sprintf(coinText, "%d", map->getPlayer()->getCoins());
	reinterpret_cast<Label *>(element)->setText(coinText);
}

void IngameScreen::init(const int width, const int height, const int scale)
{
	std::shared_ptr<Texture> iconTexture = TextureRegistry::getTexture("icons");
	if (!iconTexture)
		throw XException("Could not initializes ingame screen. Icon texture is not loaded!");

	Font *font_bold = FontRegistry::getFont("lazytown_bold" + std::to_string(scale));
	if (!font_bold)
		throw XException("Could not initialize ingame screen. Font is not loaded!");

	Vector4f cloudWhite(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);

	float pixelSize = 1.0f / 256.0f;
	float guiScale = static_cast<float>(scale);

	Vector4f healthIconUv(0.0f, 0.0f, pixelSize * 16.0f, pixelSize * 14.0f);
	Vector4f coinIconUv(pixelSize * 16.0f, 0.0f, pixelSize * 30.0f, pixelSize * 14.0f);

	this->m_healthIcon = new Image(5.0f * guiScale, 5.0f * guiScale, 0, 16 * guiScale, 14 * guiScale, iconTexture, healthIconUv);
	this->m_coinIcon = new Image(6.0f * guiScale, 25.0f * guiScale, 1, 14 * guiScale, 14 * guiScale, iconTexture, coinIconUv);

	this->m_healthLabel = new Label(25.0f * guiScale, 7 * guiScale, 2, "0", font_bold, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	this->m_healthLabel->setUpdateCallback(healthLabelUpdateCallback);
	this->m_coinLabel = new Label(25.0f * guiScale, 27.0f * guiScale, 3, "0", font_bold, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	this->m_coinLabel->setUpdateCallback(coinLabelUpdateCallback);
	this->m_roundLabel = new Label(5.0f * guiScale, static_cast<float>(height) - (5.0f * guiScale), 4, "Round: 0/50", font_bold, cloudWhite, CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT);

	this->addElement(this->m_healthIcon);
	this->addElement(this->m_coinIcon);
	this->addElement(this->m_healthLabel);
	this->addElement(this->m_coinLabel);
	this->addElement(this->m_roundLabel);
	this->setVisibility(true);
}