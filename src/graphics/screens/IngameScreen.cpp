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
	this->m_waveLabel = nullptr;
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

	this->m_selectedTowerLabel = nullptr;
	this->m_selectedTowerLevelLabel = nullptr;
	this->m_selectedTowerAttackRadiusIcon = nullptr;
	this->m_selectedTowerAttackRadiusLabel = nullptr;
	this->m_selectedTowerUpgradedAttackRadiusLabel = nullptr;
	this->m_selectedTowerDamageIcon = nullptr;
	this->m_selectedTowerDamageLabel = nullptr;
	this->m_selectedTowerUpgradedDamageLabel = nullptr;
	this->m_selectedTowerAttackSpeedIcon = nullptr;
	this->m_selectedTowerAttackSpeedLabel = nullptr;
	this->m_selectedTowerUpgradedAttackSpeedLabel = nullptr;
	this->m_selectedTowerPriceIcon = nullptr;
	this->m_selectedTowerPriceLabel = nullptr;
	this->m_upgradeTowerButton = nullptr;

	this->m_startWaveButton = nullptr;

	ScreenRegistry::registerScreen(this);
}

IngameScreen::~IngameScreen()
{
	delete this->m_healthIcon;
	delete this->m_coinIcon;
	delete this->m_healthLabel;
	delete this->m_coinLabel;
	delete this->m_waveLabel;
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
	delete this->m_selectedTowerLabel;
	delete this->m_selectedTowerLevelLabel;
	delete this->m_selectedTowerAttackRadiusIcon;
	delete this->m_selectedTowerAttackRadiusLabel;
	delete this->m_selectedTowerUpgradedAttackRadiusLabel;
	delete this->m_selectedTowerDamageIcon;
	delete this->m_selectedTowerDamageLabel;
	delete this->m_selectedTowerUpgradedDamageLabel;
	delete this->m_selectedTowerAttackSpeedIcon;
	delete this->m_selectedTowerAttackSpeedLabel;
	delete this->m_selectedTowerUpgradedAttackSpeedLabel;
	delete this->m_selectedTowerPriceIcon;
	delete this->m_selectedTowerPriceLabel;
	delete this->m_upgradeTowerButton;
	delete this->m_startWaveButton;
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
	TDMap *map = dynamic_cast<TDMap *>(cedar::EngineThread::getInstance()->getLoadedScene());
	char coinText[] = "000000";
	sprintf(coinText, "%d", map->getPlayer()->getCoins());
	reinterpret_cast<Label *>(element)->setText(coinText);
}

void buyTowerButtonInteractHandler(Element *element)
{
	if (EngineThread::getInstance()->getGameState() == CEDAR_STATE_RUNNING)
	{
		dynamic_cast<IngameScreen *>(ScreenRegistry::getScreen("ingameScreen"))->setSelectedTower(nullptr);

		TDMap *map = dynamic_cast<TDMap *>(EngineThread::getInstance()->getLoadedScene());

		Vector3f origin;
		Vector3f rayDir;

		OpenGLThread::getInstance()->getMasterRenderer()->getMouseRay(&origin, &rayDir);

		float r = -(origin.y / rayDir.y);

		Vector3f planeIntersection = origin + (rayDir * r);

		TowerEntity *ghostTower = new TowerEntity(cedar::Entity::nextEntityId(), planeIntersection, TOWER_CANON);
		map->setSelectedTower(ghostTower);
		EngineThread::getInstance()->setGameState(TOC_STATE_PLACING);
	}
}

void upgradeTowerButtonInteractHandler(Element *element)
{
	TDMap *map = dynamic_cast<TDMap *>(EngineThread::getInstance()->getLoadedScene());

	TowerEntity *selectedTower = map->getSelectedTower();
	selectedTower->setLevel(selectedTower->getLevel() + 1);
	map->getPlayer()->addCoins(-TowerInfo::getTowerInfo(selectedTower->getTowerType())->getLevelInfo(selectedTower->getLevel())->getPrice());
	dynamic_cast<IngameScreen *>(ScreenRegistry::getScreen("ingameScreen"))->setSelectedTower(selectedTower);
}

void startWaveButtonInteractHandler(Element *element)
{
	TDMap *map = dynamic_cast<TDMap *>(EngineThread::getInstance()->getLoadedScene());
	map->startNextWave();
	element->setEnabled(false);
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
	Vector4f gray(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);
	Vector4f green(0x52 / 255.0f, 0xB3 / 255.0f, 0x47 / 255.0f, 1.0f);
	Vector4f red(0xCC / 255.0f, 0x49 / 255.0f, 0x3D / 255.0f, 1.0f);

	float pixelSize = 1.0f / 256.0f;
	float guiScale = static_cast<float>(scale);

	Vector4f healthIconUv(0.0f, 0.0f, pixelSize * 16.0f, pixelSize * 14.0f);
	Vector4f coinIconUv(pixelSize * 16.0f, 0.0f, pixelSize * 30.0f, pixelSize * 14.0f);
	Vector4f shopBackgroundUv(0.0f, 0.0f, pixelSize * 108.0f, pixelSize * 228.0f);
	Vector4f smallCoinIconUv(30.0f * pixelSize, 0.0f, 39.0f * pixelSize, 9.0f * pixelSize);
	Vector4f attackRangeIconUv(39.0f * pixelSize, 0.0f, 48.0f * pixelSize, 9.0f * pixelSize);
	Vector4f damageIconUv(61.0f * pixelSize, 0.0f, 70.0f * pixelSize, 9.0f * pixelSize);
	Vector4f attackSpeedIconUv(48.0f * pixelSize, 0.0f, 61.0f * pixelSize, 7.0f * pixelSize);

	unsigned char zIndex = 0;
	unsigned int alignmentBL = CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT;

	this->m_healthIcon = new Image(5.0f * guiScale, 5.0f * guiScale, zIndex++, 16 * guiScale, 14 * guiScale, iconTexture, healthIconUv);
	this->m_coinIcon = new Image(6.0f * guiScale, 25.0f * guiScale, zIndex++, 14 * guiScale, 14 * guiScale, iconTexture, coinIconUv);

	this->m_healthLabel = new Label(25.0f * guiScale, 7 * guiScale, zIndex++, "0", font_bold, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	this->m_healthLabel->setUpdateCallback(healthLabelUpdateCallback);
	this->m_coinLabel = new Label(25.0f * guiScale, 27.0f * guiScale, zIndex++, "0", font_bold, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	this->m_coinLabel->setUpdateCallback(coinLabelUpdateCallback);
	this->m_waveLabel = new Label(5.0f * guiScale, static_cast<float>(height) - (5.0f * guiScale), zIndex++, "Wave: 0/" + std::to_string(WaveInfo::getWaveCount()), font_bold, cloudWhite, alignmentBL);

	this->m_shopBackground = new Image(static_cast<float>(width) - (108.0f * guiScale), 0.0f, zIndex++, 108.0f * guiScale, 228.0f * guiScale,
									   guiTexture, shopBackgroundUv, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);

	this->m_buyCanonButton = new ImageButton(static_cast<float>(width) - (101.0f * guiScale), 25.0f * guiScale, zIndex++, 20.0f * guiScale, 20.0f * guiScale,
											 iconTexture,
											 Vector4f(20.0f * pixelSize, 14.0f * pixelSize, 40.0f * pixelSize, 34.0f * pixelSize),
											 Vector4f(20.0f * pixelSize, 34.0f * pixelSize, 40.0f * pixelSize, 54.0f * pixelSize),
											 Vector4f(20.0f * pixelSize, 54.0f * pixelSize, 40.0f * pixelSize, 74.0f * pixelSize));
	this->m_buyCanonButton->setInteractCallback(buyTowerButtonInteractHandler);

	const LevelInfo *canonLevelInfo = TowerInfo::getTowerInfo(TOWER_CANON)->getLevelInfo(0);

	this->m_canonCoinIcon = new Image(static_cast<float>(width) - (69.0f * guiScale), 24.0f * guiScale, zIndex++,
									  9.0f * guiScale, 9.0f * guiScale, iconTexture, smallCoinIconUv);
	this->m_canonCoinLabel = new Label(static_cast<float>(width) - (57.0f * guiScale), 31.0f * guiScale, zIndex++,
									   std::to_string(canonLevelInfo->getPrice()), font, cloudWhite, alignmentBL);

	this->m_canonAttackRangeIcon = new Image(static_cast<float>(width) - (79.0f * guiScale), 36.0f * guiScale, zIndex++,
											 9.0f * guiScale, 9.0f * guiScale, iconTexture, attackRangeIconUv);
	this->m_canonAttackRangeLabel = new Label(static_cast<float>(width) - (67.0f * guiScale), 43.0f * guiScale, zIndex++,
											  std::to_string(canonLevelInfo->getAttackRadius()), font, cloudWhite, alignmentBL);

	this->m_canonDamageIcon = new Image(static_cast<float>(width) - (55.0f * guiScale), 36.0f * guiScale, zIndex++,
										9.0f * guiScale, 9.0f * guiScale, iconTexture, damageIconUv);
	this->m_canonDamageLabel = new Label(static_cast<float>(width) - (43.0f * guiScale), 43.0f * guiScale, zIndex++,
										 std::to_string(canonLevelInfo->getDamage()), font, cloudWhite, alignmentBL);

	this->m_canonAttackSpeedIcon = new Image(static_cast<float>(width) - (31.0f * guiScale), 37.0f * guiScale, zIndex++,
											 13.0f * guiScale, 7.0f * guiScale, iconTexture, attackSpeedIconUv);
	this->m_canonAttackSpeedLabel = new Label(static_cast<float>(width) - (15.0f * guiScale), 43.0f * guiScale, zIndex++,
											  std::to_string(canonLevelInfo->getAttackSpeed()), font, cloudWhite, alignmentBL);


	this->m_selectedTowerLabel = new Label(static_cast<float>(width) - (102.0f * guiScale), 12.0f * guiScale, zIndex++,
										   "Canon", font, cloudWhite, alignmentBL);

	this->m_selectedTowerLevelLabel = new Label(static_cast<float>(width) - (102.0f * guiScale), 145.0f * guiScale, zIndex++,
												"Level: 1", font, cloudWhite, alignmentBL);

	this->m_selectedTowerAttackRadiusIcon = new Image(static_cast<float>(width) - (100.0f * guiScale), 150.0f * guiScale, zIndex++,
													  9.0f * guiScale, 9.0f * guiScale, iconTexture, attackRangeIconUv);
	this->m_selectedTowerAttackRadiusLabel = new Label(static_cast<float>(width) - (86.0f * guiScale), 157.0f * guiScale, zIndex++,
													   "1", font, cloudWhite, alignmentBL);
	this->m_selectedTowerUpgradedAttackRadiusLabel = new Label(static_cast<float>(width) - (73.0f * guiScale), 157.0f * guiScale, zIndex++,
															   "+1", font, green, alignmentBL);

	this->m_selectedTowerDamageIcon = new Image(static_cast<float>(width) - (100.0f * guiScale), 162.0f * guiScale, zIndex++,
												9.0f * guiScale, 9.0f * guiScale, iconTexture, damageIconUv);
	this->m_selectedTowerDamageLabel = new Label(static_cast<float>(width) - (86.0f * guiScale), 169.0f * guiScale, zIndex++,
												 "1", font, cloudWhite, alignmentBL);
	this->m_selectedTowerUpgradedDamageLabel = new Label(static_cast<float>(width) - (73.0f * guiScale), 169.0f * guiScale, zIndex++,
														 "+1", font, green, alignmentBL);

	this->m_selectedTowerAttackSpeedIcon = new Image(static_cast<float>(width) - (102.0f * guiScale), 175.0f * guiScale, zIndex++,
													 13.0f * guiScale, 7.0f * guiScale, iconTexture, attackSpeedIconUv);
	this->m_selectedTowerAttackSpeedLabel = new Label(static_cast<float>(width) - (86.0f * guiScale), 181.0f * guiScale, zIndex++,
													  "1", font, cloudWhite, alignmentBL);
	this->m_selectedTowerUpgradedAttackSpeedLabel = new Label(static_cast<float>(width) - (73.0f * guiScale), 181.0f * guiScale, zIndex++,
															  "+1", font, green, alignmentBL);

	this->m_selectedTowerPriceIcon = new Image(static_cast<float>(width) - (100.0f * guiScale), 186.0f * guiScale, zIndex++,
											   9.0f * guiScale, 9.0f * guiScale, iconTexture, smallCoinIconUv);
	this->m_selectedTowerPriceLabel = new Label(static_cast<float>(width) - (86.0f * guiScale), 193.0f * guiScale, zIndex++,
												"-50", font, red, alignmentBL);

	Vector4f buttonDefaultUV(108.0f * pixelSize, 168.0f * pixelSize, 204.0f * pixelSize, 192.0f * pixelSize);
	Vector4f buttonHoveredUV(108.0f * pixelSize, 192.0f * pixelSize, 204.0f * pixelSize, 216.0f * pixelSize);
	Vector4f buttonPressedUV(108.0f * pixelSize, 216.0f * pixelSize, 204.0f * pixelSize, 240.0f * pixelSize);
	this->m_upgradeTowerButton = new ImageButton(static_cast<float>(width) - (102.0f * guiScale), 198.0f * guiScale, zIndex,
												 96.0f * guiScale, 24.0f * guiScale, guiTexture, buttonDefaultUV, buttonHoveredUV, buttonPressedUV,
												 "Upgrade", font, cloudWhite, cloudWhite, gray, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	this->m_upgradeTowerButton->setDefaultCaptionOffset(-1.0f - (2.0f * guiScale));
	this->m_upgradeTowerButton->setHoveredCaptionOffset(-1.0f - (2.0f * guiScale));
	this->m_upgradeTowerButton->setPressedCaptionOffset(-1.0f);
	this->m_upgradeTowerButton->setInteractCallback(upgradeTowerButtonInteractHandler);

	this->setUpgradeAreaVisible(false);

	Vector4f startButtonDefaultUV(108.0f * pixelSize, 0.0f, 130.0f * pixelSize, 24.0f * pixelSize);
	Vector4f startButtonHoveredUV(130.0f * pixelSize, 0.0f, 152.0f * pixelSize, 24.0f * pixelSize);
	Vector4f startButtonPressedUV(152.0f * pixelSize, 0.0f, 174.0f * pixelSize, 24.0f * pixelSize);
	this->m_startWaveButton = new ImageButton(static_cast<float>(width) - (26.0f * guiScale), static_cast<float>(height) - (28.0f * guiScale), zIndex++,
											  22.0f * guiScale, 24.0f * guiScale, guiTexture, startButtonDefaultUV, startButtonHoveredUV, startButtonPressedUV);
	this->m_startWaveButton->setInteractCallback(startWaveButtonInteractHandler);

	this->addElement(this->m_healthIcon);
	this->addElement(this->m_coinIcon);
	this->addElement(this->m_healthLabel);
	this->addElement(this->m_coinLabel);
	this->addElement(this->m_waveLabel);
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
	this->addElement(this->m_selectedTowerLabel);
	this->addElement(this->m_selectedTowerLevelLabel);
	this->addElement(this->m_selectedTowerAttackRadiusIcon);
	this->addElement(this->m_selectedTowerAttackRadiusLabel);
	this->addElement(this->m_selectedTowerUpgradedAttackRadiusLabel);
	this->addElement(this->m_selectedTowerDamageIcon);
	this->addElement(this->m_selectedTowerDamageLabel);
	this->addElement(this->m_selectedTowerUpgradedDamageLabel);
	this->addElement(this->m_selectedTowerAttackSpeedIcon);
	this->addElement(this->m_selectedTowerAttackSpeedLabel);
	this->addElement(this->m_selectedTowerUpgradedAttackSpeedLabel);
	this->addElement(this->m_selectedTowerPriceIcon);
	this->addElement(this->m_selectedTowerPriceLabel);
	this->addElement(this->m_upgradeTowerButton);
	this->addElement(this->m_startWaveButton);
	this->setVisibility(true);
}

void IngameScreen::onUpdate(unsigned long currentTime, unsigned long tickCount)
{
	Screen::onUpdate(currentTime, tickCount);

	TDMap *map = dynamic_cast<TDMap *>(EngineThread::getInstance()->getLoadedScene());

	this->m_buyCanonButton->setEnabled(map->getPlayer()->getCoins() >= 200);

	if (this->m_upgradeTowerButton->isVisible())
	{
		TDMap *map = dynamic_cast<TDMap *>(EngineThread::getInstance()->getLoadedScene());

		TowerEntity *selectedTower = map->getSelectedTower();

		if (selectedTower->getLevel() < TowerInfo::getTowerInfo(selectedTower->getTowerType())->getLevels() - 1)
		{
			int upgradePrice = TowerInfo::getTowerInfo(selectedTower->getTowerType())->getLevelInfo(selectedTower->getLevel() + 1)->getPrice();
			this->m_upgradeTowerButton->setEnabled(upgradePrice <= map->getPlayer()->getCoins());
		}
	}
}

void IngameScreen::setUpgradeAreaVisible(const bool visible)
{
	this->m_selectedTowerLabel->setVisibility(visible);
	this->m_selectedTowerLevelLabel->setVisibility(visible);
	this->m_selectedTowerAttackRadiusIcon->setVisibility(visible);
	this->m_selectedTowerAttackRadiusLabel->setVisibility(visible);
	this->m_selectedTowerUpgradedAttackRadiusLabel->setVisibility(visible);
	this->m_selectedTowerDamageIcon->setVisibility(visible);
	this->m_selectedTowerDamageLabel->setVisibility(visible);
	this->m_selectedTowerUpgradedDamageLabel->setVisibility(visible);
	this->m_selectedTowerAttackSpeedIcon->setVisibility(visible);
	this->m_selectedTowerAttackSpeedLabel->setVisibility(visible);
	this->m_selectedTowerUpgradedAttackSpeedLabel->setVisibility(visible);
	this->m_selectedTowerPriceIcon->setVisibility(visible);
	this->m_selectedTowerPriceLabel->setVisibility(visible);
	this->m_upgradeTowerButton->setVisibility(visible);
}

void IngameScreen::setSelectedTower(TowerEntity *selectedTower)
{
	if (selectedTower)
	{
		const TowerInfo *towerInfo = TowerInfo::getTowerInfo(selectedTower->getTowerType());
		const LevelInfo *levelInfo = towerInfo->getLevelInfo(selectedTower->getLevel());
		this->m_selectedTowerLabel->setText(towerInfo->getName());

		char levelCaption[] = "Level: X";
		sprintf(levelCaption, "Level: %d", selectedTower->getLevel() + 1);
		this->m_selectedTowerLevelLabel->setText(levelCaption);
		this->m_selectedTowerAttackRadiusLabel->setText(std::to_string(levelInfo->getAttackRadius()));
		this->m_selectedTowerDamageLabel->setText(std::to_string(levelInfo->getDamage()));
		this->m_selectedTowerAttackSpeedLabel->setText(std::to_string(levelInfo->getAttackSpeed()));

		unsigned int nextLevel = selectedTower->getLevel() + 1;
		if (nextLevel >= towerInfo->getLevels())
		{
			this->m_selectedTowerPriceLabel->setText("-");
			this->m_upgradeTowerButton->setEnabled(false);
			this->m_upgradeTowerButton->setCaption("Max Level");

			this->m_selectedTowerUpgradedAttackRadiusLabel->setText("");
			this->m_selectedTowerUpgradedDamageLabel->setText("");
			this->m_selectedTowerUpgradedAttackSpeedLabel->setText("");
		}
		else
		{
			const LevelInfo *nextLevelInfo = towerInfo->getLevelInfo(nextLevel);
			int price = nextLevelInfo->getPrice();
			this->m_selectedTowerPriceLabel->setText("-" + std::to_string(price));

			int attackRadiusDifference = nextLevelInfo->getAttackRadius() - levelInfo->getAttackRadius();
			int damageDifference = nextLevelInfo->getDamage() - levelInfo->getDamage();
			int attackSpeedDifference = nextLevelInfo->getAttackSpeed() - levelInfo->getAttackSpeed();

			this->m_selectedTowerUpgradedAttackRadiusLabel->setText(attackRadiusDifference == 0 ? "" : ("+" + std::to_string(attackRadiusDifference)));
			this->m_selectedTowerUpgradedDamageLabel->setText(damageDifference == 0 ? "" : ("+" + std::to_string(damageDifference)));
			this->m_selectedTowerUpgradedAttackSpeedLabel->setText(attackSpeedDifference == 0 ? "" : ("+" + std::to_string(attackSpeedDifference)));

			this->m_upgradeTowerButton->setEnabled(price <= dynamic_cast<TDMap *>(cedar::EngineThread::getInstance()->getLoadedScene())->getPlayer()->getCoins());
			this->m_upgradeTowerButton->setCaption("Upgrade");
		}

		this->setUpgradeAreaVisible(true);
	}
	else
	{
		this->setUpgradeAreaVisible(false);
	}
}

void IngameScreen::setStartWaveButtonEnabled(const bool enabled)
{
	this->m_startWaveButton->setEnabled(enabled);
}

void IngameScreen::setCurrentWave(const unsigned int currentWave) {
	this->m_waveLabel->setText("Wave: " + std::to_string(currentWave) + "/" + std::to_string(WaveInfo::getWaveCount()));
}
