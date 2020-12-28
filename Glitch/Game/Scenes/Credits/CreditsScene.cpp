#include "pch.h"
#include "CreditsScene.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void CreditsScene::onAttach()
{
	loadButtons();
	loadText();
	loadBackground();
	loadMusic();
	loadAnimations();
}

/// @brief 
/// Create all text for this scene
void CreditsScene::loadText() {
	shared_ptr<Text> name1 = shared_ptr<Text>(new Text(4, new ColoredText("Lars Jansen", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X - LEFT_X_CENTER, CENTER_Y - 150));
	shared_ptr<Text> name2 = shared_ptr<Text>(new Text(5, new ColoredText("Max van Nistelrooij", Color(0, 0, 0), false), LONG_NAME_WIDTH, TEXT_HEIGHT, CENTER_X - LEFT_X_CENTER, CENTER_Y + 50));
	shared_ptr<Text> name3 = shared_ptr<Text>(new Text(6, new ColoredText("Thijs de leeuw", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X - LEFT_X_CENTER, CENTER_Y + 250));
	shared_ptr<Text> name4 = shared_ptr<Text>(new Text(7, new ColoredText("Rinke de Vries", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X + RIGHT_X_CENTER, CENTER_Y - 150));
	shared_ptr<Text> name5 = shared_ptr<Text>(new Text(8, new ColoredText("William Ross", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X + RIGHT_X_CENTER, CENTER_Y + 50));
	shared_ptr<Text> name6 = shared_ptr<Text>(new Text(9, new ColoredText("Wouter van Hees", Color(0, 0, 0), false), LONG_NAME_WIDTH, TEXT_HEIGHT, CENTER_X + RIGHT_X_CENTER, CENTER_Y + 250));
	shared_ptr<Text> name7 = shared_ptr<Text>(new Text(10, new ColoredText("Foxtrot", Color(0, 0, 0), false), 500, 75, CENTER_X - 350, CENTER_Y + 650));
	this->text.push_back(name1);
	this->text.push_back(name2);
	this->text.push_back(name3);
	this->text.push_back(name4);
	this->text.push_back(name5);
	this->text.push_back(name6);
	this->text.push_back(name7);

	for (size_t i = 0; i < this->text.size(); i++)
	{
		addNewObjectToLayer(3, this->text[i]);
	}
}
/// @brief 
/// Create all buttons for this scene
void CreditsScene::loadButtons() {
	// Back button
	auto backBtn = shared_ptr<SecondaryButton>(new SecondaryButton(3, "To Main Menu", onBackClick, this->dispatcher));
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	addNewObjectToLayer(5, backBtn);
}

/// @brief 
/// Create the background for this scene
void CreditsScene::loadBackground() {
	shared_ptr<SpriteObject> bg = shared_ptr<SpriteObject>(new SpriteObject(-1012, 1080, 1920, 1, 300, "Assets/Backgrounds/credits_foreground.png"));
	shared_ptr<Drawable> bgLayer = shared_ptr<Drawable>(new Drawable(13));
	bgLayer->setStatic(true);
	bgLayer->setPositionX(0);
	bgLayer->setPositionY(1080);
	bgLayer->setWidth(1920);
	bgLayer->setHeight(1080);
	bgLayer->registerSprite(SpriteState::DEFAULT, bg);
	bgLayer->changeToState(SpriteState::DEFAULT);

	shared_ptr<SpriteObject>BG_IMAGE = shared_ptr<SpriteObject>(new SpriteObject(-1011, 1080, 1920, 1, 300, "Assets/Backgrounds/game_win_layer_0.png"));

	shared_ptr<Drawable> bgImage = shared_ptr<Drawable>(new Drawable(15));
	bgImage->setStatic(true);
	bgImage->setPositionX(0);
	bgImage->setPositionY(1080);
	bgImage->setWidth(1920);
	bgImage->setHeight(1080);
	bgImage->registerSprite(SpriteState::DEFAULT, BG_IMAGE);
	bgImage->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(4, bgLayer, false, true);
	addNewObjectToLayer(0, bgImage, false, true);
}

/// @brief 
/// Load the sounds for this scene
void CreditsScene::loadMusic() {
	engine->loadSound("GOOD_GAME", "Assets/Sound/applause.wav");
}

/// @brief 
/// Create the sounds for this scene
void CreditsScene::start(bool playSound)
{
	if(playSound)engine->startSound("GOOD_GAME");
}

void CreditsScene::onUpdate(float deltaTime)
{
	for (size_t i = 0; i < this->text.size(); i++)
	{
		this->text[i]->setPositionY(this->text[i]->getPositionY() - 1);
		if (text[i]->getPositionY() == 0) this->text[i]->setPositionY(WINDOW_HEIGHT);
	}

	handleAnimation(deltaTime);

	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, true);
	}

}

/// @brief 
/// Remove the sounds of the soundengine
void CreditsScene::onDetach()
{
	Scene::onDetach();
}


/// @brief 
/// Load the animatio for the screen
void CreditsScene::loadAnimations() {

	shared_ptr<SpriteObject> SLIME_JUMP = shared_ptr<SpriteObject>(new SpriteObject(-992883, 24, 33, 1, 300, "Assets/Sprites/Enemies/Slime/Slime_action_2.png"));
	shared_ptr<SpriteObject> SLIME_FALL = shared_ptr<SpriteObject>(new SpriteObject(-992884, 24, 33, 1, 300, "Assets/Sprites/Enemies/Slime/Slime_action_3.png"));

	animation = shared_ptr<Drawable>(new Drawable(35));
	animation->setStatic(true);
	animation->setPositionX(1675);
	animation->setPositionY(948);
	animation->setWidth(213);
	animation->setHeight(177);
	animation->registerSprite(SpriteState::DEFAULT, SLIME_JUMP);
	animation->registerSprite(SpriteState::AIR_JUMP_RIGHT, SLIME_JUMP);
	animation->registerSprite(SpriteState::AIR_FALL_RIGHT, SLIME_FALL);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	addNewObjectToLayer(2, animation);
}

/// @brief 
/// Handle the fake animation in the screen
void CreditsScene::handleAnimation(float deltaTime) {
	if (animation->getPositionY() < 648) {
		animation->changeToState(SpriteState::AIR_FALL_RIGHT);
		falling = true;
	}
	else if (animation->getPositionY() > 860) {
		animation->changeToState(SpriteState::AIR_JUMP_RIGHT);
		falling = false;
	}

	if (falling) {
		animation->setPositionY(animation->getPositionY() + deltaTime * 300);
	}
	else {
		animation->setPositionY(animation->getPositionY() + deltaTime * -300);
	}
}