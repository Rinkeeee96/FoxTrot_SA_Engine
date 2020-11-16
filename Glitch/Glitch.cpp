#pragma once
#include "pch.h"
#include "Glitch.h"
#include "./Game/Level.h"
#include "./Game/SpriteState.h"
#include "./Game/Player/Player.h"
#include <Engine\Events\Window\WindowCloseEvent.h>
#include "SceneSwitcher/SceneSwitcher.h"
#include "Game/Screens/MainMenu.h"
#include "Game/Screens/DeadScreen.h"
#include <Game\Screens\WinScreen.h>

// TODO engine.h & engine.cpp

// Doxygen
// Cntrl + / above function or class to generate Doxygen
// https://devblogs.microsoft.com/cppblog/doxygen-and-xml-doc-comment-support/
// Installing
// https://computingonplains.wordpress.com/doxygen-and-visual-studio/

Engine engine;
bool gameRunning = true;

void sceneTestSetup()
{
	SpriteObject* so0 = new SpriteObject(1, 16, 16, 1, 300, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");

	SpriteObject* so1 = new SpriteObject(100, 37, 50, 1, 300, "Assets/Sprites/Character/adventure.png");
	SpriteObject* so2 = new SpriteObject(101, 37, 50, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png");

	SpriteObject* so7 = new SpriteObject(106, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_left.png");
	SpriteObject* so3 = new SpriteObject(102, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");

	SpriteObject* so4 = new SpriteObject(103, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_slide.png");

	SpriteObject* so5 = new SpriteObject(104, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png");
	SpriteObject* so8 = new SpriteObject(107, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");

	SpriteObject* so6 = new SpriteObject(105, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png");
	SpriteObject* so9 = new SpriteObject(108, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png");

	map<string, string> soundL1 = {
		{"Level_1_Sound", "Assets/Sound/file_example_WAV_1MG.wav"},
	};

	Level* testScene = new Level(100, WINDOW_HEIGHT, WINDOW_WIDTH*3, soundL1);

	Drawable* object2 = new Player(2);
	testScene->setObjectToFollow(object2);
	object2->setDensity(1);
	object2->setJumpHeight(100);
	object2->setStatic(false);
	object2->setPositionX(800);
	object2->setPositionY(100);
	object2->registerSprite(SpriteState::DEFAULT, so1);
	object2->registerSprite(SpriteState::AIR_ATTACK, so2);
	object2->registerSprite(SpriteState::RUN_RIGHT, so3);
	object2->registerSprite(SpriteState::SLIDE, so4);
	object2->registerSprite(SpriteState::AIR_FALL_LEFT, so5);
	object2->registerSprite(SpriteState::AIR_JUMP_LEFT, so6);
	object2->registerSprite(SpriteState::AIR_FALL_RIGHT, so8);
	object2->registerSprite(SpriteState::AIR_JUMP_RIGHT, so9);
	object2->registerSprite(SpriteState::RUN_LEFT, so7);
	object2->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, object2);

	object2->setScale(7);


	auto* staticGround = new Drawable(101);
	staticGround->setWidth(500); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(1); // x 20 left down
	staticGround->setPositionY(540);// y 300 left down
	staticGround->setStatic(true);
	staticGround->registerSprite(SpriteState::DEFAULT, so0);
	staticGround->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround);

	staticGround = new Drawable(102);
	staticGround->setWidth(500); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(501); // x 20 left down
	staticGround->setPositionY(540);// y 300 left down
	staticGround->setStatic(true);
	staticGround->registerSprite(SpriteState::DEFAULT, so0);
	staticGround->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround);

	staticGround = new Drawable(103);
	staticGround->setWidth(500); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(1100); // x 20 left down
	staticGround->setPositionY(500);// y 300 left down
	staticGround->setStatic(true);
	staticGround->registerSprite(SpriteState::DEFAULT, so0);
	staticGround->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround);

	staticGround = new Drawable(104);
	staticGround->setWidth(5000); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(1200); // x 20 left down
	staticGround->setPositionY(450);// y 300 left down
	staticGround->setStatic(true);
	staticGround->registerSprite(SpriteState::DEFAULT, so0);
	staticGround->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround);

	staticGround = new Drawable(105);
	staticGround->setWidth(250); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(1); // x 20 left down
	staticGround->setPositionY(330);// y 300 left down
	staticGround->setStatic(true);
	staticGround->registerSprite(SpriteState::DEFAULT, so0);
	staticGround->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround);

	SpriteObject* particle1Sprite = new SpriteObject(11, 20, 20, 20, 300, "Assets/Particles/fire.png");
	engine.loadSprite(*particle1Sprite);

	ParticleAdapter* particle1 = new ParticleAdapter(12);        // create a new particle system pointer
	particle1->registerSprite(SpriteState::DEFAULT, particle1Sprite);
	particle1->changeToState(SpriteState::DEFAULT);
	particle1->setPositionX(1700);
	particle1->setPositionY(384);
	particle1->setStyle(ParticleInit::ParticleStyle::FIRE);    // set the example effects
	testScene->addNewObjectToLayer(4, particle1);

	ParticleAdapter* particle2 = new ParticleAdapter(13);        // create a new particle system pointer
	particle2->registerSprite(SpriteState::DEFAULT, particle1Sprite);
	particle2->changeToState(SpriteState::DEFAULT);
	particle2->setPositionX(100);
	particle2->setPositionY(384);
	particle2->setStyle(ParticleInit::ParticleStyle::FIRE);    // set the example effects
	testScene->addNewObjectToLayer(2, particle2);

	auto* staticGround2 = new Drawable(119);
	staticGround2->setWidth(20); // width
	staticGround2->setHeight(80);// height
	staticGround2->setPositionX(250); // x 20 left down
	staticGround2->setPositionY(540);// y 300 left down
	staticGround2->setStatic(true);
	staticGround2->setFriction(0);
	staticGround2->registerSprite(SpriteState::DEFAULT, so0);
	staticGround2->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround2);

	auto* staticGround3 = new Drawable(120);
	staticGround3->setWidth(30); // width
	staticGround3->setHeight(80);// height
	staticGround3->setPositionX(480); // x 20 left down
	staticGround3->setPositionY(540);// y 300 left down
	staticGround3->setStatic(true);
	staticGround3->registerSprite(SpriteState::DEFAULT, so0);
	staticGround3->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround3);

	auto* staticGround4 = new Drawable(121);
	staticGround4->setWidth(30); // width
	staticGround4->setHeight(140);// height
	staticGround4->setPositionX(320); // x 20 left down
	staticGround4->setPositionY(540);// y 300 left down
	staticGround4->setStatic(true);
	staticGround4->registerSprite(SpriteState::DEFAULT, so0);
	staticGround4->changeToState(SpriteState::DEFAULT);
	testScene->addNewObjectToLayer(1, staticGround4);

	SceneSwitcher::get_instance().RegisterScene("GAME", testScene);
}

bool StopLoop(Event& event) {
	gameRunning = false;
	return true;
}

int main() {
	SceneSwitcher::get_instance().SetEngine(&engine);
	sceneTestSetup();
	MainMenu* mainMenu = new MainMenu(1);
	DeadScreen* deadScreen = new DeadScreen(2);
	WinScreen* winScreen = new WinScreen(3);
	SceneSwitcher::get_instance().RegisterScene("MAIN_MENU", mainMenu);
	SceneSwitcher::get_instance().RegisterScene("DEAD_SCREEN", deadScreen);
	SceneSwitcher::get_instance().RegisterScene("WIN_SCREEN", winScreen);
	SceneSwitcher::get_instance().SwitchToScene("DEAD_SCREEN");

	EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(StopLoop);

	engine.startTickThreads();
	while (gameRunning)
	{
		AppTickEvent60 appTick;
		AppTickEvent30 appTick30;

		engine.pollEvents();
		EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
		EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

		this_thread::sleep_for(chrono::milliseconds(10));
	}
	
}
