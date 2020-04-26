//
// Created by masy on 27.01.20.
//

#include <GameOverScreen.hpp>
#include <WinScreen.hpp>
#include "cedar/TextureRegistry.hpp"
#include "cedar/ScreenRegistry.hpp"
#include "cedar/MeshCollider2D.hpp"
#include "cedar/EngineThread.hpp"
#include "cedar/OpenGLThread.hpp"
#include "cedar/Screen.hpp"
#include "cedar/FontRegistry.hpp"
#include "cedar/Image.hpp"
#include "cedar/Math.hpp"
#include "cedar/ModelRegistry.hpp"

#include "ToC.h"
#include "ToCLogAppender.h"
#include "KeyHandler.h"
#include "SceneRenderer.h"
#include "DebugRenderer.h"
#include "TDMap.h"
#include "IngameScreen.hpp"
#include "DebugScreen.hpp"
#include "EscapeScreen.hpp"
#include "Enemies.hpp"
#include "Waves.hpp"

ToC::ToC()
{
	this->m_config = new ToCConfig();
}

ToC *ToC::getInstance()
{
	static ToC *instance = new ToC();
	return instance;
}

void ToC::loadMap() const
{
	unsigned char bitmask;
	Model *enemyModel = cedar::ModelRegistry::loadBMFModel("enemy", "resources/models/enemy.bmf", &bitmask);
	glBindVertexArray(enemyModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, enemyModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void *) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void *) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Load map data

	// Model
	Model *terrainModel = cedar::ModelRegistry::loadBMFModel("map1", "resources/models/map1_world.bmf", &bitmask);
	glBindVertexArray(terrainModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, terrainModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void *) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void *) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Collision data
	std::ifstream collisionFile;
	collisionFile.open("resources/models/map1_noBuildZone.bmf", std::ifstream::binary | std::ifstream::ate);
	if (!collisionFile.is_open())
	{
		throw XException("Could not load map data!");
	}

	unsigned int fileSize = collisionFile.tellg();
	collisionFile.seekg(0, std::ios_base::beg);

	unsigned char mode = 0;
	unsigned char bitMask = 0;
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

	collisionFile.read(reinterpret_cast<char *>(&mode), 1);
	collisionFile.read(reinterpret_cast<char *>(&bitMask), 1);
	collisionFile.read(reinterpret_cast<char *>(&vertexCount), 4);
	collisionFile.read(reinterpret_cast<char *>(&indexCount), 4);

	if (mode != 0x02u)
		throw XException("Collision data has wrong format!");

	if (bitMask != 0x0)
		throw XException("Collision vertex data has wrong information!");

	unsigned int vertexDataSize = vertexCount * 12;
	unsigned int indexDataSize = indexCount * 4;
	unsigned int expectedFileSize = vertexDataSize + indexDataSize + 10;
	if (fileSize < expectedFileSize)
		throw XException("Corrupted collision data!");

	Vector3f *vertexData = new Vector3f[vertexCount];
	unsigned int *indexData = new unsigned int[indexCount];
	collisionFile.read(reinterpret_cast<char *>(vertexData), vertexDataSize);
	collisionFile.read(reinterpret_cast<char *>(indexData), indexDataSize);
	collisionFile.close();

	Vector2f *vertices = new Vector2f[vertexCount];
	for (unsigned int n = 0; n < vertexCount; n++)
	{
		vertices[n] = Vector2f(vertexData[n].x, vertexData[n].z);
	}
	cedar::Triangle *triangles = reinterpret_cast<Triangle *>(indexData);
	delete[] vertexData;
	MeshCollider2D *noBuildZone = new MeshCollider2D(vertices, indexCount / 3, triangles);

	// Path data
	std::ifstream pathFile;
	pathFile.open("resources/models/map1_path.bmf", std::ifstream::binary | std::ifstream::ate);
	if (!pathFile.is_open())
		throw XException("Could not load path data!");

	fileSize = pathFile.tellg();
	pathFile.seekg(0, std::ios_base::beg);

	pathFile.read(reinterpret_cast<char *>(&mode), 1);
	pathFile.read(reinterpret_cast<char *>(&bitMask), 1);
	pathFile.read(reinterpret_cast<char *>(&vertexCount), 4);
	pathFile.read(reinterpret_cast<char *>(&indexCount), 4);

	if (mode != 0x00u)
		throw XException("Path data has wrong format!");

	if (bitMask != 0x00u)
		throw XException("Path vertex data has wrong information!");

	vertexDataSize = vertexCount * 12;
	indexDataSize = indexCount * 4;
	expectedFileSize = vertexDataSize + indexDataSize + 10;
	if (fileSize < expectedFileSize)
		throw XException("Corrupted collision path!");

	Vector3f *pathPoints = new Vector3f[vertexCount];
	pathFile.read(reinterpret_cast<char *>(pathPoints), vertexDataSize);
	pathFile.close();

	Player *player = new Player(20, 225);
	TDMap *map = new TDMap(Vector3f(0.0f, 0.0f, 0.0f), player, terrainModel, noBuildZone, vertexCount, pathPoints);
	EngineThread::getInstance()->loadScene(map);
}

void ToC::initTowers() const
{
	unsigned char bitmask;
	Model *towerModel = cedar::ModelRegistry::loadBMFModel("towerCanon_level0", "resources/models/towerCanon_level0.bmf", &bitmask);
	glBindVertexArray(towerModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, towerModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void *) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void *) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	towerModel = cedar::ModelRegistry::loadBMFModel("towerCanon_level1", "resources/models/towerCanon_level1.bmf", &bitmask);
	glBindVertexArray(towerModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, towerModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void *) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void *) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	towerModel = cedar::ModelRegistry::loadBMFModel("towerCanon_level2", "resources/models/towerCanon_level2.bmf", &bitmask);
	glBindVertexArray(towerModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, towerModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void *) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void *) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	towerModel = cedar::ModelRegistry::loadBMFModel("towerCanon_level3", "resources/models/towerCanon_level3.bmf", &bitmask);
	glBindVertexArray(towerModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, towerModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void *) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void *) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	int levels = 4;
	LevelInfo *canonLevelInfo = new LevelInfo[levels];
	canonLevelInfo[0].set(200, 1.0f, 2.2f, 1.0f, 5.0f, 1, "towerCanon_level0");
	canonLevelInfo[1].set(50, 1.0f, 2.2f, 1.0f, 5.0f, 2, "towerCanon_level1");
	canonLevelInfo[2].set(100, 1.0f, 2.2f, 2.0f, 5.0f, 2, "towerCanon_level2");
	canonLevelInfo[3].set(200, 1.0f, 2.2f, 4.0f, 6.0f, 2, "towerCanon_level3");

	TowerInfo::registerTowerInfo(TOWER_CANON, new TowerInfo("Canon", levels, canonLevelInfo));
}

void ToC::initEnemies() const
{
	EnemyInfo::registerEnemyInfo(LEVEL1, new EnemyInfo(1, Vector3f(0xD3 / 255.0f, 0x50 / 255.0f, 0x50 / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL2, new EnemyInfo(2, Vector3f(0x6F / 255.0f, 0xD3 / 255.0f, 0x50 / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL3, new EnemyInfo(3, Vector3f(0x50 / 255.0f, 0x8C / 255.0f, 0xD3 / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL4, new EnemyInfo(4, Vector3f(0xD3 / 255.0f, 0xCF / 255.0f, 0x50 / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL5, new EnemyInfo(5, Vector3f(0xD3 / 255.0f, 0x50 / 255.0f, 0xC3 / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL6, new EnemyInfo(8, Vector3f(0x72 / 255.0f, 0x50 / 255.0f, 0xD3 / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL7, new EnemyInfo(10, Vector3f(0x50 / 255.0f, 0xD3 / 255.0f, 0xAE / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL8, new EnemyInfo(15, Vector3f(0xD7 / 255.0f, 0xD6 / 255.0f, 0xCA / 255.0f)));
	EnemyInfo::registerEnemyInfo(LEVEL9, new EnemyInfo(20, Vector3f(0x2A / 255.0f, 0x28 / 255.0f, 0x27 / 255.0f)));
}

void ToC::initWaves() const
{
	unsigned int enemyCount = 40;
	EnemyType *enemies = new EnemyType[enemyCount]{
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE
	};
	WaveInfo::registerWaveInfo(1, new WaveInfo(enemyCount, enemies));

	enemyCount = 60;
	enemies = new EnemyType[enemyCount]{
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE
	};
	WaveInfo::registerWaveInfo(2, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
	};
	WaveInfo::registerWaveInfo(3, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL1, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE
	};
	WaveInfo::registerWaveInfo(4, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
	};
	WaveInfo::registerWaveInfo(5, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL1, NONE, LEVEL1, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
	};
	WaveInfo::registerWaveInfo(6, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
	};
	WaveInfo::registerWaveInfo(7, new WaveInfo(enemyCount, enemies));

	enemyCount = 60;
	enemies = new EnemyType[enemyCount]{
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL2, NONE, NONE, NONE,
			LEVEL3, NONE, NONE, NONE,
			LEVEL3, NONE, NONE, NONE,
			LEVEL3, NONE, NONE, NONE,
			LEVEL3, NONE, NONE, NONE,
			LEVEL3, NONE, NONE, NONE,
	};
	WaveInfo::registerWaveInfo(8, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL3, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
	};
	WaveInfo::registerWaveInfo(9, new WaveInfo(enemyCount, enemies));

	enemyCount = 40;
	enemies = new EnemyType[enemyCount]{
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL2, NONE, LEVEL2, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
			LEVEL3, NONE, LEVEL3, NONE,
	};
	WaveInfo::registerWaveInfo(10, new WaveInfo(enemyCount, enemies));
}

void ToC::initCallback(MasterRenderer *masterRenderer)
{
	OpenGLThread::getInstance()->getWindow()->setTitle("ToC");
	masterRenderer->addRenderer(SceneRenderer::getInstance());
	masterRenderer->setClearColor(Vector4f(0x27 / 255.0f, 0x87 / 255.0f, 0xB8 / 255.0f, 1.0f));

	FontRegistry::loadFont("lazytown3", "resources/fonts/lazytown.ptf", 3, 0, 255, CEDAR_RENDERING_SHARP);

	FontRegistry::loadFont("lazytown_bold2", "resources/fonts/lazytown_bold.ptf", 2, 0, 255, CEDAR_RENDERING_SHARP);
	FontRegistry::loadFont("lazytown_bold3", "resources/fonts/lazytown_bold.ptf", 3, 0, 255, CEDAR_RENDERING_SHARP);

	std::shared_ptr<Texture> iconTexture = TextureRegistry::loadTexture("icons", "resources/gui/icons.png");
	iconTexture->setParameteri(CEDAR_TEXTURE_MAG_FILTER, CEDAR_NEAREST);

	std::shared_ptr<Texture> guiTexture = TextureRegistry::loadTexture("gui", "resources/gui/gui.png");
	guiTexture->setParameteri(CEDAR_TEXTURE_MAG_FILTER, CEDAR_NEAREST);

	Window *window = OpenGLThread::getInstance()->getWindow();

	this->initTowers();
	this->initEnemies();
	this->initWaves();
	this->loadMap();

	IngameScreen *ingameScreen = new IngameScreen();
	ingameScreen->init(window->getWidth(), window->getHeight(), 3);

	GameOverScreen *gameOverScreen = new GameOverScreen();
	gameOverScreen->init(window->getWidth(), window->getHeight(), 3);

	WinScreen *winScreen = new WinScreen();
	winScreen->init(window->getWidth(), window->getHeight(), 3);

	DebugScreen *debugScreen = new DebugScreen();
	debugScreen->init(window->getWidth(), window->getHeight(), 2);

	EscapeScreen *escapeScreen = new EscapeScreen();
	escapeScreen->init(window->getWidth(), window->getHeight(), 3);
}

void ToC::preStart()
{
	config = new Config(1920, 1080, 60, -1, false, 90.0f);

	ToCLogAppender *logAppender = new ToCLogAppender();
	LoggerFactory::setQueueLogAppender(logAppender);
	logAppender->start();

	cedar::EngineThread::getInstance()->setInitCallback([]() {
		Camera *cam = new Camera(toRadians(10.0f), toRadians(70.0f));
		EngineThread::getInstance()->setCamera(cam);
	});

	cedar::OpenGLThread::getInstance()->setInitCallback(std::bind(&ToC::initCallback, this, std::placeholders::_1));
	cedar::OpenGLThread::getInstance()->setInputCallback(KeyHandler::handle);
}

void ToC::onStart()
{
	// Nothing to do here
}

void ToC::onStop()
{
	TowerInfo::cleanup();
	EnemyInfo::cleanup();
	WaveInfo::cleanup();
}