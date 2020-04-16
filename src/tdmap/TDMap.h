//
// Created by masy on 11.03.20.
//

#ifndef TALESOFCATVENTURE_TDMAP_H
#define TALESOFCATVENTURE_TDMAP_H

#include "cedar/Scene.hpp"
#include "cedar/MeshCollider2D.hpp"
#include "TowerEntity.h"
#include "Player.hpp"

class TDMap : public cedar::Scene
{
private:
	Player *m_player;
	cedar::MeshCollider2D *m_noBuildZone;
	unsigned int m_pathPointCount;
	const cedar::Vector3f *m_pathPoints;

	std::vector<TowerEntity*> m_towers;
	TowerEntity *m_selectedTower;
	cedar::Matrix4f *m_transformationMatrix;

public:
	TDMap(const cedar::Vector3f &position, Player *player, cedar::Model *model, cedar::MeshCollider2D *noBuildZone, unsigned int pathPointCount, const cedar::Vector3f *pathPoints);
	~TDMap() override;

	[[nodiscard]] bool isPositionValid(const cedar::Vector2f &position, float radius) const;
	[[nodiscard]] TowerEntity *getTower(const cedar::Vector3f &cameraOrigin, const cedar::Vector3f &rayDir);

	void update(unsigned long currentTime, unsigned long tickCount) override;
	void render(unsigned long currentTime, unsigned long tickCount, const cedar::ShaderProgram *shader) override;

	void addTower(TowerEntity *towerEntity);
	void removeTower(TowerEntity *towerEntity);

	[[nodiscard]] TowerEntity *getSelectedTower() const;
	void setSelectedTower(TowerEntity *newGhostTower);

	[[nodiscard]] unsigned int getPathPointCount() const;
	[[nodiscard]] const cedar::Vector3f *getPathPoints() const;

	[[nodiscard]] Player *getPlayer() const;
};

#endif //TALESOFCATVENTURE_TDMAP_H
