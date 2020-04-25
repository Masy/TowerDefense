//
// Created by masy on 19.04.20.
//

#include <cedar/ScreenRegistry.hpp>
#include <cedar/TextureRegistry.hpp>
#include <cedar/FontRegistry.hpp>
#include <cedar/EngineThread.hpp>
#include <cedar/OpenGLThread.hpp>
#include <cedar/ModelRegistry.hpp>
#include <GameStates.h>
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
	this->m_shopBackground = nullptr;
	this->m_buyCanonButton = nullptr;
	this->m_canonCoinIcon = nullptr;
	this->m_canonCoinLabel = nullptr;
	this->m_canonAttackRangeIcon = nullptr;
	this->m_canonAttackRangeLabel = nullptr;
	this->m_canonDamageIcon = nullptr;
	this->m_canonDamageLabel = nullptr;
	this->m_canonAttackSpeedIcon = nullptr;
	this->m_canonAttackSpeedLabel = nullptr;

	ScreenRegistry::registerScreen(this);
}

IngameScreen::~IngameScreen()
{
	delete this->m_healthIcon;
	delete this->m_coinIcon;
	delete this->m_healthLabel;
	delete this->m_coinLabel;
	delete this->m_roundLabel;
	delete this->m_shopBackground;
	delete this->m_buyCanonButton;
	delete this->m_canonCoinIcon;
	delete this->m_canonCoinLabel;
	delete this->m_canonAttackRangeIcon;
	delete this->m_canonAttackRangeLabel;
	delete this->m_canonDamageIcon;
	delete this->m_canonDamageLabel;
	delete this->m_canonAttackSpeedIcon;
	delete this->m_canonAttackSpeedLabel;
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

void buyTowerButtonUpdateHandler(Element *element, const unsigned long currentTime, const unsigned long currentTick)
{
	TDMap *map = dynamic_cast<TDMap*>(EngineThread::getInstance()->getLoadedScene());

	if (map)
	{
		if (map->getPlayer()->getCoins() >= 200)
		{
			element->setEnabled(true);
			return;
		}
	}

	element->setEnabled(false);
}

void buyTowerButtonInteractHandler(Element *element)
{
	TDMap *map = dynamic_cast<TDMap*>(EngineThread::getInstance()->getLoadedScene());

	if (EngineThread::getInstance()->getGameState() == CEDAR_STATE_RUNNING)
	{
		Vector3f origin;
		Vector3f rayDir;

		OpenGLThread::getInstance()->getMasterRenderer()->getMouseRay(&origin, &rayDir);

		float r = -(origin.y / rayDir.y);

		Vector3f planeIntersection = origin + (rayDir * r);

		TowerEntity *ghostTower = new TowerEntity(cedar::Entity::nextEntityId(), planeIntersection, TOWER_CANON);
		ghostTower->setModel(ModelRegistry::getModel(TowerInfo::getTowerInfo(TOWER_CANON)->getLevelInfo(0)->getModelName()));
		map->setSelectedTower(ghostTower);
		EngineThread::getInstance()->setGameState(TOC_STATE_PLACING);
	}
}

void IngameScreen::init(const int width, const int height, const int scale)
{
	std::shared_ptr<Texture> iconTexture = TextureRegistry::getTexture("icons");
	if (!iconTexture)
		throw XException("Could not initializes ingame screen. Icon texture is not loaded!");

	std::shared_ptr<Texture> guiTexture = TextureRegistry::getTexture("gui");
	if (!guiTexture)
		throw XException("Could not initializes ingame screen. GUI texture is not loaded!");

	std::shared_ptr<Font> font = FontRegistry::getFont("lazytown" + std::to_string(scale));
	if (!font)
		throw XException("Could not initialize ingame screen. Font is not loaded!");

	std::shared_ptr<Font> font_bold = FontRegistry::getFont("lazytown_bold" + std::to_string(scale));
	if (!font_bold)
		throw XException("Could not initialize ingame screen. Bold font is not loaded!");

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

	Vector4f shopBackgroundUv(0.0f, 0.0f, pixelSize * 108.0f, pixelSize * 215.0f);
	this->m_shopBackground = new Image(static_cast<float>(width), 0.0f, 5, 108.0f * guiScale, 215.0f * guiScale, guiTexture, shopBackgroundUv, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_RIGHT);

	this->m_buyCanonButton = new ImageButton(static_cast<float>(width) - (101.0f * guiScale), 25.0f * guiScale, 6, 20.0f * guiScale, 20.0f * guiScale,
											 iconTexture,
											 Vector4f(20.0f * pixelSize, 14.0f * pixelSize, 40.0f * pixelSize, 34.0f * pixelSize),
											 Vector4f(20.0f * pixelSize, 34.0f * pixelSize, 40.0f * pixelSize, 54.0f * pixelSize),
											 Vector4f(20.0f * pixelSize, 54.0f * pixelSize, 40.0f * pixelSize, 74.0f * pixelSize));

	this->m_buyCanonButton->setUpdateCallback(buyTowerButtonUpdateHandler);
	this->m_buyCanonButton->setInteractCallback(buyTowerButtonInteractHandler);

	const LevelInfo *canonLevelInfo = TowerInfo::getTowerInfo(TOWER_CANON)->getLevelInfo(0);

	this->m_canonCoinIcon = new Image(static_cast<float>(width) - (69.0f * guiScale), 24.0f * guiScale, 7, 9.0f * guiScale, 9.0f * guiScale,
									  iconTexture, Vector4f(30.0f * pixelSize, 0.0f, 39.0f * pixelSize, 9.0f * pixelSize));
	this->m_canonCoinLabel = new Label(static_cast<float>(width) - (57.0f * guiScale), 31.0f * guiScale, 8, std::to_string(canonLevelInfo->getPrice()), font, cloudWhite, CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT);

	this->m_canonAttackRangeIcon = new Image(static_cast<float>(width) - (79.0f * guiScale), 36.0f * guiScale, 9, 9.0f * guiScale, 9.0f * guiScale,
											 iconTexture, Vector4f(39.0f * pixelSize, 0.0f, 48.0f * pixelSize, 9.0f * pixelSize));
	this->m_canonAttackRangeLabel = new Label(static_cast<float>(width) - (67.0f * guiScale), 43.0f * guiScale, 10, std::to_string(canonLevelInfo->getAttackRadius()), font, cloudWhite, CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT);

	this->m_canonDamageIcon = new Image(static_cast<float>(width) - (55.0f * guiScale), 36.0f * guiScale, 11, 9.0f * guiScale, 9.0f * guiScale,
										iconTexture, Vector4f(61.0f * pixelSize, 0.0f, 70.0f * pixelSize, 9.0f * pixelSize));
	this->m_canonDamageLabel = new Label(static_cast<float>(width) - (43.0f * guiScale), 43.0f * guiScale, 12, std::to_string(canonLevelInfo->getDamage()), font, cloudWhite, CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT);

	this->m_canonAttackSpeedIcon = new Image(static_cast<float>(width) - (31.0f * guiScale), 37.0f * guiScale, 13, 13.0f * guiScale, 7.0f * guiScale,
											 iconTexture, Vector4f(48.0f * pixelSize, 0.0f, 61.0f * pixelSize, 7.0f * pixelSize));
	this->m_canonAttackSpeedLabel = new Label(static_cast<float>(width) - (15.0f * guiScale), 43.0f * guiScale, 14, std::to_string(canonLevelInfo->getAttackSpeed()), font, cloudWhite, CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT);

	this->addElement(this->m_healthIcon);
	this->addElement(this->m_coinIcon);
	this->addElement(this->m_healthLabel);
	this->addElement(this->m_coinLabel);
	this->addElement(this->m_roundLabel);
	this->addElement(this->m_shopBackground);
	this->addElement(this->m_buyCanonButton);
	this->addElement(this->m_canonCoinIcon);
	this->addElement(this->m_canonCoinLabel);
	this->addElement(this->m_canonAttackRangeIcon);
	this->addElement(this->m_canonAttackRangeLabel);
	this->addElement(this->m_canonDamageIcon);
	this->addElement(this->m_canonDamageLabel);
	this->addElement(this->m_canonAttackSpeedIcon);
	this->addElement(this->m_canonAttackSpeedLabel);
	this->setVisibility(true);
}