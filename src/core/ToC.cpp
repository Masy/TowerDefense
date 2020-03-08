//
// Created by masy on 27.01.20.
//

#include <cedar/ScreenRegistry.h>
#include "cedar/EngineThread.h"
#include "cedar/OpenGLThread.h"
#include "cedar/Screen.h"
#include "ToC.h"
#include "ToCLogAppender.h"
#include "KeyHandler.h"
#include "TerrainRenderer.h"
#include "cedar/Button.h"
#include "cedar/FontRegistry.h"
#include "cedar/Label.h"
#include "cedar/Math.h"

ToC::ToC()
{
	this->m_config = new ToCConfig();
}

ToC *ToC::getInstance()
{
	static ToC *instance = new ToC();
	return instance;
}

void ToC::preStart()
{
	config = new Config(1280, 720, 60, -1, false, 90.0f);

	ToCLogAppender *logAppender = new ToCLogAppender();
	LoggerFactory::setQueueLogAppender(logAppender);
	logAppender->start();

	cedar::EngineThread::getInstance()->setInitCallback([]() {
		EngineThread::getInstance()->setCamera(new Camera());
	});

	cedar::OpenGLThread::getInstance()->setInitCallback([](MasterRenderer *masterRenderer) {
		OpenGLThread::getInstance()->getWindow()->setTitle("ToC");
		masterRenderer->addRenderer(new TerrainRenderer());

		Font *lazytown = FontRegistry::loadFont("lazytown", "fonts/Lazytown.ttf", 14, CEDAR_RENDERING_SMOOTH);

		Screen *screen = new Screen("screen", 1);

		// #ecf0f0
		Vector4f cloudWhite = Vector4f(0xEC / 255.0f, 0xF0 / 255.0f, 0xF0 / 255.0f, 1.0f);
		// #bdc3c7
		Vector4f gray = Vector4f(0xBD / 255.0f, 0xC3 / 255.0f, 0xC7 / 255.0f, 1.0f);
		// #95a5a6
		Vector4f background = Vector4f(0x95 / 255.0f, 0xA5 / 255.0f, 0xA5 / 255.0f, 1.0f);
		// #3498db
		Vector4f hoverBlue = Vector4f(0x34 / 255.0f, 0x98 / 255.0f, 0xDB / 255.0f, 1.0f);
		// #2980b9
		Vector4f pressBlue = Vector4f(0x29 / 255.0f, 0x80 / 255.0f, 0xB9 / 255.0f, 1.0f);
		// #e74c3c
		Vector4f hoverRed = Vector4f(0xE7 / 255.0f, 0x4C / 255.0f, 0x3C / 255.0f, 1.0f);
		// #c0392b
		Vector4f pressRed = Vector4f(0xC0 / 255.0f, 0x39 / 255.0f, 0x2B / 255.0f, 1.0f);

		Button *buttonOption = new Button(640.0f, 325.0f, 0, 180.0f, 30.0f, "Options", lazytown, cloudWhite, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
		buttonOption->setBackgroundColor(background);
		buttonOption->setHoveredBackgroundColor(hoverBlue);
		buttonOption->setPressedBackgroundColor(pressBlue);
		buttonOption->setPressedTextColor(gray);

		Button *buttonClose = new Button(640.0f, 360.0f, 1, 180.0f, 30.0f, "Close", lazytown, cloudWhite, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
		buttonClose->setBackgroundColor(background);
		buttonClose->setHoveredBackgroundColor(hoverBlue);
		buttonClose->setPressedBackgroundColor(pressBlue);
		buttonClose->setPressedTextColor(gray);
		buttonClose->setInteractCallback([=](Element *element) {
			screen->setVisibility(false);
		});

		Button *buttonExit = new Button(640.0f, 410.0f, 2, 180.0f, 30.0f, "Exit", lazytown, cloudWhite, CEDAR_ALIGNMENT_CENTER | CEDAR_ALIGNMENT_MIDDLE);
		buttonExit->setBackgroundColor(background);
		buttonExit->setHoveredBackgroundColor(hoverRed);
		buttonExit->setPressedBackgroundColor(pressRed);
		buttonExit->setPressedTextColor(gray);
		buttonExit->setInteractCallback([=](Element *element) {
			Cedar::getInstance()->stop();
		});

		screen->addElement(buttonOption);
		screen->addElement(buttonClose);
		screen->addElement(buttonExit);

		Label *fpsLabel = new Label(5.0f, 5.0f, 0, "FPS: 0", lazytown, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
		fpsLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
			if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS()) == 0)
			{
				char fpsText[24];
				sprintf(fpsText, "FPS: %.0f", std::round(OpenGLThread::getInstance()->getFPS()));
				reinterpret_cast<Label*>(element)->setText(fpsText);
			}
		});
		Label *frameTimeLabel = new Label(5.0f, 25.0f , 1, "FrameTime: 0.0", lazytown, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
		frameTimeLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
			if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 4) == 0)
			{
				char frameTimeText[24];
				sprintf(frameTimeText, "FrameTime: %.2f", OpenGLThread::getInstance()->getLastFrameTime() * 1000.0);
				reinterpret_cast<Label*>(element)->setText(frameTimeText);
			}

		});
		Label *positionLabel = new Label(5.0f, 45.0f, 2, "Pos: 0.0, 0.0, 0.0", lazytown, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
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
		Label *rotationLabel = new Label(5.0f, 65.0f, 3, "Rot: 0.0, 0.0, 0.0", lazytown, cloudWhite, CEDAR_ALIGNMENT_TOP | CEDAR_MOUSE_BUTTON_LEFT);
		rotationLabel->setUpdateCallback([](Element *element, unsigned long currentTime, unsigned long tickCount) {
			if (tickCount % static_cast<unsigned long>(OpenGLThread::getInstance()->getTPS() / 20) == 0)
			{
				Camera *camera = EngineThread::getInstance()->getCamera();
				if (camera)
				{
					const Vector3f rot = *camera->getRotationEuler();
					char rotationText[] = "Rot: 00.00, 000.00, 000.00";
					sprintf(rotationText, "Rot: %.2f, %.2f, %.2f", cedar::toDegrees(rot.x), cedar::toDegrees(rot.y), cedar::toDegrees(rot.z));
					reinterpret_cast<Label*>(element)->setText(rotationText);
				}
			}
		});

		Screen *debugScreen = new Screen("debug", 0);
		debugScreen->addElement(fpsLabel);
		debugScreen->addElement(frameTimeLabel);
		debugScreen->addElement(positionLabel);
		debugScreen->addElement(rotationLabel);

		ScreenRegistry::registerScreen(debugScreen);
		ScreenRegistry::registerScreen(screen);
	});

}

void ToC::onStart()
{
	cedar::OpenGLThread::getInstance()->setInputCallback([] (unsigned long currentTime, unsigned long tickCount, const InputHandler *inputHandler) {
		KeyHandler::handle(inputHandler);
	});
}

void ToC::onStop()
{

}