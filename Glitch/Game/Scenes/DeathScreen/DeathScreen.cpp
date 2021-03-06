#include "pch.h"
#include "DeathScreen.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&DeathScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

/// @brief Loads the screen on attach.
void DeathScreen::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

/// @brief 
/// Create all buttons for this scene
void DeathScreen::loadButtons() {
	auto btnSprite = shared_ptr<SpriteObject>(new SpriteObject(-599, 40, 116, 1, 300, "Assets/Buttons/btn_gray_round.png"));

	shared_ptr<Button> startBtn = shared_ptr<Button>(new Button(-600, ColoredText("Restart", Color(0, 0, 0)), onReStartBtnClick, btnSprite, this->dispatcher));
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);

	shared_ptr<Button> mainBtn = shared_ptr<Button>(new Button(-601, ColoredText("Overworld", Color(0, 0, 0)), onOverworldBtnClick, btnSprite, this->dispatcher));
	mainBtn->setPositionX(CENTER_X - mainBtn->getWidth() / 2);
	mainBtn->setPositionY(CENTER_Y - mainBtn->getHeight() / 2 + 100);

	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, mainBtn);
}

/// @brief 
/// Create the background for this scene
void DeathScreen::loadBackground() {
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-605, 1080, 1920, 1, 300, "Assets/Backgrounds/game_over_Layer_0.png"));
	shared_ptr<SpriteObject> BG_LAYER_ADVENTRUE = shared_ptr<SpriteObject>(new SpriteObject(-606, 37, 50, 7, 300, "Assets/Sprites/Character/adventure_die.png"));
	BG_LAYER_ADVENTRUE->freezeOn(7);
	shared_ptr<SpriteObject> BG_LAYER_2 = shared_ptr<SpriteObject>(new SpriteObject(-607, 1080, 1920, 1, 300, "Assets/Backgrounds/game_over_Layer_1.png"));

	shared_ptr<Drawable> layer0 = shared_ptr<Drawable>(new Drawable(-602));
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> animation = shared_ptr<Drawable>(new Drawable(-604));
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	shared_ptr<Drawable> layer2 = shared_ptr<Drawable>(new Drawable(-603));
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
void DeathScreen::loadMusic() {
	engine->loadSound("DEAD_SOUND", "Assets/Sound/game_over_looped.wav");
}

/// @brief 
/// Create the sounds for this scene
void DeathScreen::start(bool playSound)
{
	if(playSound)engine->startSound("DEAD_SOUND");
}

/// @brief
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void DeathScreen::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		if (nextScene == "") {

			nextScene = stateMachine->getCurrentLevelIdentifier();
		}
		stateMachine->switchToScene(nextScene, true);
	}
}

/// @brief 
/// Remove the sounds of the soundengine
void DeathScreen::onDetach()
{
	Scene::onDetach();
}
