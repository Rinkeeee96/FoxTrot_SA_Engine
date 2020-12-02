#include "pch.h"
#include "MainMenu.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&MainMenu::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void MainMenu::onAttach()
{
	
	loadButtons();
	loadBackground();
	loadMusic();
}

/// @brief 
/// Create all buttons for this scene
void MainMenu::loadButtons() {

	auto* startBtn = new PrimaryButton(10, "Start", BIND_FN(onStartBtnClick), this->dispatcher);
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);

	auto* creditsBtn = new PrimaryButton(12, "Credits", BIND_FN(onCreditsBtnClick));
	creditsBtn->setPositionX(CENTER_X - creditsBtn->getWidth() / 2);
	creditsBtn->setPositionY(CENTER_Y - creditsBtn->getHeight() / 2 + 200);

	auto* stopBtn = new SecondaryButton(13, "Stop", BIND_FN(onStopBtnClick), this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());


	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, stopBtn);
	//addNewObjectToLayer(3, loadBtn);
	addNewObjectToLayer(3, creditsBtn);
}

/// @brief 
/// Create the background for this scene
void MainMenu::loadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-1010, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-1011, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-1012, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(14);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(15);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(16);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, animation, false, true);
	addNewObjectToLayer(2, layer2, false, true);
}

/// @brief 
/// Load the sounds for this scene
void MainMenu::loadMusic() {
	engine.soundEngine.onLoadBackgroundMusicEvent("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
/// Create the sounds for this scene
void MainMenu::start()
{
	engine.soundEngine.onStartBackgroundMusicEvent("MENU_SOUND");
}

void MainMenu::onUpdate()
{
}

/// @brief 
/// Remove the sounds of the soundengine
void MainMenu::onDetach()
{
	engine.soundEngine.onStartBackgroundMusicEvent("MENU_SOUND");
	Scene::onDetach();
}


/// @brief 
/// A callback function for startBtn
/// Start transition scene to OVERWORLD
void MainMenu::onStartBtnClick()
{
	stateMachine.switchToScene("SaveScreen", false);
}


/// @brief 
/// A callback function for stopBTN
/// Stop the application
void MainMenu::onStopBtnClick() {
	engine.setEngineRunning(false);
}


/// @brief 
/// A callback function for creditsBTN
/// Start transition scene to DEAD_SCREEN
void MainMenu::onCreditsBtnClick() {
	
}


/// @brief 
/// A callback function for loadBtn
/// Start transition scene to WIN_SCREEN
void MainMenu::onLoadBtnClick() {
	cout << "Load button click" << endl;
}
