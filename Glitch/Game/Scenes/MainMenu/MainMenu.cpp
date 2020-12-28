#include "pch.h"
#include "MainMenu.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

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

	shared_ptr<PrimaryButton> startBtn = shared_ptr<PrimaryButton>(new PrimaryButton(10, "Start", onStartBtnClick, this->dispatcher));
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);

	shared_ptr<PrimaryButton> mappingBtn = shared_ptr<PrimaryButton>(new PrimaryButton(13, "Mapping", onMappingBtnClick, this->dispatcher));
	mappingBtn->setPositionX(CENTER_X - mappingBtn->getWidth() / 2);
	mappingBtn->setPositionY(CENTER_Y - mappingBtn->getHeight() / 2 + 100);

	shared_ptr<PrimaryButton> creditsBtn = shared_ptr<PrimaryButton>(new PrimaryButton(12, "Credits", onCreditsBtnClick, this->dispatcher));
	creditsBtn->setPositionX(CENTER_X - creditsBtn->getWidth() / 2);
	creditsBtn->setPositionY(CENTER_Y - creditsBtn->getHeight() / 2 + 200);

	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(14, "Exit", onStopBtnClick, this->dispatcher));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());


	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, mappingBtn);
	addNewObjectToLayer(3, creditsBtn);
	addNewObjectToLayer(3, stopBtn);
}

/// @brief 
/// Create the background for this scene
void MainMenu::loadBackground() {
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-1010, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png"));
	shared_ptr<SpriteObject> BG_LAYER_ADVENTRUE = shared_ptr<SpriteObject>(new SpriteObject(-1011, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png"));
	shared_ptr<SpriteObject> BG_LAYER_2 = shared_ptr<SpriteObject>(new SpriteObject(-1012, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png"));

	shared_ptr<Drawable> layer0 = shared_ptr<Drawable>(new Drawable(14));
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> animation = shared_ptr<Drawable>(new Drawable(15));
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);
	
	shared_ptr<Drawable> layer2 = shared_ptr<Drawable>(new Drawable(16));
	layer2->setStatic(true);
	layer2->setPositionX(0);
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
	engine->loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
/// Create the sounds for this scene
void MainMenu::start(bool playSound)
{
	if(playSound)engine->startSound("MENU_SOUND");
}

/// @brief
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void MainMenu::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound|playMusicCredits);
	}
}

/// @brief 
/// Remove the sounds of the soundengine
void MainMenu::onDetach()
{
	Scene::onDetach();
}
