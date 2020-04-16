//
// Created by masy on 27.01.20.
//

#include "cedar/TextureRegistry.hpp"
#include "cedar/ScreenRegistry.hpp"
#include "cedar/MeshCollider2D.hpp"
#include "cedar/EngineThread.hpp"
#include "cedar/OpenGLThread.hpp"
#include "cedar/Screen.hpp"
#include "cedar/Button.hpp"
#include "cedar/FontRegistry.hpp"
#include "cedar/Label.hpp"
#include "cedar/Image.hpp"
#include "cedar/Math.hpp"
#include "cedar/ModelRegistry.hpp"

#include "ToC.h"
#include "ToCLogAppender.h"
#include "KeyHandler.h"
#include "SceneRenderer.h"
#include "DebugRenderer.h"
#include "TDMap.h"
#include "GameStates.h"

ToC::ToC()
{
	this->m_config = new ToCConfig();

	// #ecf0f0
	this->cloudWhite = Vector4f(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
	// #bdc3c7
	this->gray = Vector4f(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);
	// #95a5a6
	this->background = Vector4f(0x95 / 255.0f, 0xA5 / 255.0f, 0xA5 / 255.0f, 1.0f);
	// #3498db
	this->hoverBlue = Vector4f(0x34 / 255.0f, 0x98 / 255.0f, 0xDB / 255.0f, 1.0f);
	// #2980b9
	this->pressBlue = Vector4f(0x29 / 255.0f, 0x80 / 255.0f, 0xB9 / 255.0f, 1.0f);
	// #e74c3c
	this->hoverRed = Vector4f(0xE7 / 255.0f, 0x4C / 255.0f, 0x3C / 255.0f, 1.0f);
	// #c0392b
	this->pressRed = Vector4f(0xC0 / 255.0f, 0x39 / 255.0f, 0x2B / 255.0f, 1.0f);
}

ToC *ToC::getInstance()
{
	static ToC *instance = new ToC();
	return instance;
}

void ToC::createEscapeScreen(Font *font)
{
	Screen *escapeScreen = new Screen("escapeScreen", 2);

	Button *buttonOption = new Button(960.0f, 495.0f, 0, 180.0f, 40.0f, "Options", font, this->cloudWhite, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
	buttonOption->setBackgroundColor(background);
	buttonOption->setHoveredBackgroundColor(hoverBlue);
	buttonOption->setPressedBackgroundColor(pressBlue);
	buttonOption->setPressedTextColor(gray);

	Button *buttonClose = new Button(960.0f, 540.0f, 1, 180.0f, 40.0f, "Close", font, this->cloudWhite, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
	buttonClose->setBackgroundColor(background);
	buttonClose->setHoveredBackgroundColor(hoverBlue);
	buttonClose->setPressedBackgroundColor(pressBlue);
	buttonClose->setPressedTextColor(gray);
	buttonClose->setInteractCallback([=](Element *element) {
		EngineThread::getInstance()->setGameState(CEDAR_STATE_RUNNING);
		escapeScreen->setVisibility(false);
	});

	Button *buttonExit = new Button(960.0f, 600.0f, 2, 180.0f, 40.0f, "Exit", font, this->cloudWhite, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
	buttonExit->setBackgroundColor(background);
	buttonExit->setHoveredBackgroundColor(hoverRed);
	buttonExit->setPressedBackgroundColor(pressRed);
	buttonExit->setPressedTextColor(gray);
	buttonExit->setInteractCallback([=](Element *element) {
		Cedar::getInstance()->stop();
	});

	escapeScreen->addElement(buttonOption);
	escapeScreen->addElement(buttonClose);
	escapeScreen->addElement(buttonExit);
	ScreenRegistry::registerScreen(escapeScreen);
}

void ToC::createDebugScreen(Font *font)
{
	float height = static_cast<float>(OpenGLThread::getInstance()->getWindow()->getHeight()) * 0.5f;
	Label *fpsLabel = new Label(5.0f, height, 0, "FPS: 0", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
	fpsLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS()) == 0)
		{
			char fpsText[24];
			sprintf(fpsText, "FPS: %.0f", std::round(OpenGLThread::getInstance()->getFPS()));
			reinterpret_cast<Label*>(element)->setText(fpsText);
		}
	});
	Label *frameTimeLabel = new Label(5.0f, height + 20.0f , 1, "FrameTime: 0.0", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
	frameTimeLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 4) == 0)
		{
			char frameTimeText[24];
			sprintf(frameTimeText, "FrameTime: %.2f", OpenGLThread::getInstance()->getLastFrameTime() * 1000.0);
			reinterpret_cast<Label*>(element)->setText(frameTimeText);
		}

	});
	Label *positionLabel = new Label(5.0f, height + 40.0f, 2, "Pos: 0.0, 0.0, 0.0", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
	positionLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 20) == 0)
		{
			Camera *camera = EngineThread::getInstance()->getCamera();
			if (camera)
			{
				const Vector3f pos = *camera->getPosition();
				char positionText[] = "Pos: 00000.000, 00000.000, 00000.000";
				sprintf(positionText, "Pos: %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
				reinterpret_cast<Label*>(element)->setText(positionText);
			}
		}
	});
	Label *rotationLabel = new Label(5.0f, height + 60.0f, 3, "Rot: 0.0°, 0.0°, 0.0°", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
	rotationLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 20) == 0)
		{
			Camera *camera = EngineThread::getInstance()->getCamera();
			if (camera)
			{
				const Vector3f rot = *camera->getRotationEuler();
				char rotationText[] = "Rot: 00.00°, 000.00°, 000.00°";
				sprintf(rotationText, "Rot: %.2f°, %.2f°, %.2f°", cedar::toDegrees(rot.x), cedar::toDegrees(rot.y), cedar::toDegrees(rot.z));
				reinterpret_cast<Label*>(element)->setText(rotationText);
			}
		}
	});
	Label *stateLabel = new Label(5.0f, height + 80.0f, 4, "State: ingame", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	stateLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		unsigned int gameState = EngineThread::getInstance()->getGameState();


		switch (gameState)
		{
			case CEDAR_STATE_RUNNING:
				reinterpret_cast<Label*>(element)->setText("State: ingame");
				break;

			case TOC_STATE_MENU:
				reinterpret_cast<Label*>(element)->setText("State: menu");
				break;

			case TOC_STATE_PLACING:
				reinterpret_cast<Label*>(element)->setText("State: placing");
				break;

			default:
				reinterpret_cast<Label*>(element)->setText("State: unknown");
				break;
		}
	});

	Screen *debugScreen = new Screen("debug", 1);
	debugScreen->addElement(fpsLabel);
	debugScreen->addElement(frameTimeLabel);
	debugScreen->addElement(positionLabel);
	debugScreen->addElement(rotationLabel);
	debugScreen->addElement(stateLabel);

	ScreenRegistry::registerScreen(debugScreen);
}

void ToC::createIngameScreen(cedar::Font *font, const float guiScale) {
	Screen *ingameScreen = new Screen("ingameScreen", 0);

	float height = static_cast<float>(OpenGLThread::getInstance()->getWindow()->getHeight());

	std::shared_ptr<Texture> iconTexture = TextureRegistry::loadTexture("icons", "resources/gui/icons.png");
	iconTexture->setParameteri(CEDAR_TEXTURE_MAG_FILTER, CEDAR_NEAREST);

	float pixel = 1.0f / 256.0f;
	Vector4f healthBarUv = Vector4f(0.0f, 0.0f, pixel * 16.0f, pixel * 14.0f);
	Vector4f coinUv = Vector4f(pixel * 16.0f, 0.0f, pixel * 30.0f, pixel * 14.0f);

	Image *healthIcon = new Image(5 * guiScale, 5 * guiScale, 0, 16 * guiScale, 14 * guiScale, iconTexture, healthBarUv);
	Label *healthLabel = new Label(25 * guiScale, 7 * guiScale, 1, "100", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	healthLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		TDMap *map = dynamic_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
		char healthText[] = "000";
		sprintf(healthText, "%d", map->getPlayer()->getHealth());
		reinterpret_cast<Label *>(element)->setText(healthText);
	});

	Image *coinIcon = new Image(6 * guiScale, 25 * guiScale, 2, 14 * guiScale, 14 * guiScale, iconTexture, coinUv);
	Label *coinLabel = new Label(25 * guiScale, 27 * guiScale, 3, "0", font, this->cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_ALIGNMENT_LEFT);
	coinLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
		TDMap *map = dynamic_cast<TDMap*>(cedar::EngineThread::getInstance()->getLoadedScene());
		char coinText[] = "000000";
		sprintf(coinText, "%d", map->getPlayer()->getCoins());
		reinterpret_cast<Label *>(element)->setText(coinText);
	});

	Label *roundLabel = new Label(5 * guiScale, height - (5 * guiScale), 4, "Round: 0/50", font, this->cloudWhite, CEDAR_ALIGNMENT_BOTTOM | CEDAR_ALIGNMENT_LEFT);

	ingameScreen->addElement(healthIcon);
	ingameScreen->addElement(healthLabel);
	ingameScreen->addElement(coinIcon);
	ingameScreen->addElement(coinLabel);
	ingameScreen->addElement(roundLabel);
	ingameScreen->setVisibility(true);
	ScreenRegistry::registerScreen(ingameScreen);
}

void ToC::loadMap()
{
	unsigned char bitmask;
	Model *towerModel = cedar::ModelRegistry::loadBMFModel("tower", "resources/models/towerBase.bmf", &bitmask);
	glBindVertexArray(towerModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, towerModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void*) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void*) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Model *enemyModel = cedar::ModelRegistry::loadBMFModel("enemy", "resources/models/enemy.bmf", &bitmask);
	glBindVertexArray(enemyModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, enemyModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void*) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void*) 20); // vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Load map data

	// Model
	Model *terrainModel = cedar::ModelRegistry::loadBMFModel("map1", "resources/models/map1_world.bmf", &bitmask);
	glBindVertexArray(terrainModel->getVertexArrayId());
	glBindBuffer(GL_ARRAY_BUFFER, terrainModel->getVertexBufferId());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr); // vertex position
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (const void*) 12); // vertex uv
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const void*) 20); // vertex normal
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
	collisionFile.read(reinterpret_cast<char*>(vertexData), vertexDataSize);
	collisionFile.read(reinterpret_cast<char*>(indexData), indexDataSize);
	collisionFile.close();

	Vector2f *vertices = new Vector2f[vertexCount];
	for (unsigned int n = 0; n < vertexCount; n++)
	{
		vertices[n] = Vector2f(vertexData[n].x, vertexData[n].z);
	}
	cedar::Triangle *triangles = reinterpret_cast<Triangle*>(indexData);
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
	pathFile.read(reinterpret_cast<char*>(pathPoints), vertexDataSize);
	pathFile.close();

	Player *player = new Player(100, 250);
	TDMap *map = new TDMap(Vector3f(0.0f, 0.0f, 0.0f), player, terrainModel, noBuildZone, vertexCount, pathPoints);
	EngineThread::getInstance()->loadScene(map);
}

void ToC::initCallback(MasterRenderer *masterRenderer)
{
	OpenGLThread::getInstance()->getWindow()->setTitle("ToC");
	masterRenderer->addRenderer(SceneRenderer::getInstance());
	masterRenderer->setClearColor(Vector4f( 0x27 / 255.0f, 0x87 / 255.0f, 0xB8 / 255.0f, 1.0f));

	Font *lazytown2 = FontRegistry::loadFont("lazytown_2", "resources/fonts/lazytown_bold.ptf", 2, 0, 255, CEDAR_RENDERING_SHARP);
	Font *lazytown3 = FontRegistry::loadFont("lazytown_3", "resources/fonts/lazytown_bold.ptf", 3, 0, 255, CEDAR_RENDERING_SHARP);

	this->createIngameScreen(lazytown3, 3.0f);
	this->createDebugScreen(lazytown2);
	this->createEscapeScreen(lazytown2);
	this->loadMap();
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
}

void ToC::onStart()
{
	cedar::OpenGLThread::getInstance()->setInputCallback(KeyHandler::handle);
}

void ToC::onStop()
{

}