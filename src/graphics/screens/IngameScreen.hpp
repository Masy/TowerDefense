//
// Created by masy on 19.04.20.
//

#ifndef GUARDIAN_INGAMESCREEN_HPP
#define GUARDIAN_INGAMESCREEN_HPP

#include "cedar/ImageButton.hpp"
#include "cedar/Screen.hpp"
#include "cedar/Label.hpp"
#include "cedar/Image.hpp"
#include "TowerEntity.h"

using namespace cedar;

/**
 * Class representing the in-game screen.
 */
class IngameScreen : public Screen
{
private:
	/**
	 * A pointer to the health icon.
	 */
	Image *m_healthIcon;
	/**
	 * A pointer to the coin icon.
	 */
	Image *m_coinIcon;
	/**
	 * A pointer to the health label.
	 */
	Label *m_healthLabel;
	/**
	 * A pointer to the coin label.
	 */
	Label *m_coinLabel;
	/**
	 * A pointer to the wave label.
	 */
	Label *m_waveLabel;
	/**
	 * A pointer to the shop background.
	 */
	Image *m_shopBackground;
	/**
	 * A pointer to the canon buy button.
	 */
	ImageButton *m_buyCanonButton;
	/**
	 * A pointer to the canon coin icon.
	 */
	Image *m_canonCoinIcon;
	/**
	 * A pointer to the canon coin label.
	 */
	Label *m_canonCoinLabel;
	/**
	 * A pointer to the canon attack range icon.
	 */
	Image *m_canonAttackRangeIcon;
	/**
	 * A pointer to the canon attack range label.
	 */
	Label *m_canonAttackRangeLabel;
	/**
	 * A pointer to the canon damage icon.
	 */
	Image *m_canonDamageIcon;
	/**
	 * A pointer to the canon damage label.
	 */
	Label *m_canonDamageLabel;
	/**
	 * A pointer to the canon attack speed icon.
	 */
	Image *m_canonAttackSpeedIcon;
	/**
	 * A pointer to the canon attack speed label.
	 */
	Label *m_canonAttackSpeedLabel;

	/**
	 * A pointer to the selected tower name label.
	 */
	Label *m_selectedTowerLabel;
	/**
	 * A pointer to the selected tower level label.
	 */
	Label *m_selectedTowerLevelLabel;
	/**
	 * A pointer to the selected tower attack radius icon.
	 */
	Image *m_selectedTowerAttackRadiusIcon;
	/**
	 * A pointer to the selected tower attack radius label.
	 */
	Label *m_selectedTowerAttackRadiusLabel;
	/**
	 * A pointer to the upgraded selected tower attack radius label.
	 */
	Label *m_selectedTowerUpgradedAttackRadiusLabel;
	/**
	 * A pointer to the selected tower damage icon.
	 */
	Image *m_selectedTowerDamageIcon;
	/**
	 * A pointer to the selected tower damage label.
	 */
	Label *m_selectedTowerDamageLabel;
	/**
	 * A pointer to the upgraded selected tower damage label.
	 */
	Label *m_selectedTowerUpgradedDamageLabel;
	/**
	 * A pointer to the selected tower attack speed icon.
	 */
	Image *m_selectedTowerAttackSpeedIcon;
	/**
	 * A pointer to the selected tower attack speed label.
	 */
	Label *m_selectedTowerAttackSpeedLabel;
	/**
	 * A pointer to the upgraded selected tower attack speed label.
	 */
	Label *m_selectedTowerUpgradedAttackSpeedLabel;
	/**
	 * A pointer to the selected tower price icon.
	 */
	Image *m_selectedTowerPriceIcon;
	/**
	 * A pointer to the selected tower price label.
	 */
	Label *m_selectedTowerPriceLabel;
	/**
	 * A pointer to the upgrade button.
	 */
	ImageButton *m_upgradeTowerButton;
	/**
	 * A pointer to the start wave button.
	 */
	ImageButton *m_startWaveButton;

	/**
	 * Sets the visibility of all elements related to the upgrade area.
	 *
	 * @param visible Whether the elements will be visible or not.
	 */
	void setUpgradeAreaVisible(bool visible);

public:
	/**
	 * Creates a new ingame screen.
	 */
	IngameScreen();

	/**
	 * Deletes the ingame screen.
	 */
	~IngameScreen();

	/**
	 * Initializes the ingame screen.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param guiScale The scale of the gui.
	 */
	void init(int width, int height, int guiScale);

	/**
	 * Method which updates all elements in the screen.
	 *
	 * @param currentTime The current time of the frame in microseconds.
	 * @param tickCount The current tick count.
	 */
	void onUpdate(unsigned long currentTime, unsigned long currentTick) override;

	/**
	 * Sets the selected tower of the upgrade area.
	 *
	 * @param selectedTower A pointer to the selected tower.
	 */
	void setSelectedTower(TowerEntity *selectedTower);

	/**
	 * Enables or disables the start wave button.
	 *
	 * @param enabled Whether the start wave button will be enabled or not.
	 */
	void setStartWaveButtonEnabled(bool enabled);

	/**
	 * Sets the current wave.
	 *
	 * @param currentWave The current wave.
	 */
	void setCurrentWave(unsigned int currentWave);
};

#endif //GUARDIAN_INGAMESCREEN_HPP
