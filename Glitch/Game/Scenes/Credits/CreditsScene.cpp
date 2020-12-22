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
	engine->loadSound("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav");
}

/// @brief 
/// Create the sounds for this scene
void CreditsScene::start(bool playSound)
{
	if(playSound)engine->startSound("WIN_SOUND");
}

void CreditsScene::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}

	for (size_t i = 0; i < this->text.size(); i++)
	{
		this->text[i]->setPositionY(this->text[i]->getPositionY() - 1);
		if (text[i]->getPositionY() == 0) this->text[i]->setPositionY(WINDOW_HEIGHT);
	}
}

/// @brief 
/// Remove the sounds of the soundengine
void CreditsScene::onDetach()
{
	Scene::onDetach();
}
