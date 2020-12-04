#include "pch.h"
#include "CreditsScene.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&CreditsScene::function, *this)

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
	auto* name1 = new Text(4, new ColoredText("Lars Jansen", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X - LEFT_X_CENTER, CENTER_Y - 150);
	auto* name2 = new Text(5, new ColoredText("Max van Nistelrooij", Color(0, 0, 0), false), LONG_NAME_WIDTH, TEXT_HEIGHT, CENTER_X - LEFT_X_CENTER, CENTER_Y + 50);
	auto* name3 = new Text(6, new ColoredText("Thijs de leeuw", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X - LEFT_X_CENTER, CENTER_Y + 250);
	auto* name4 = new Text(7, new ColoredText("Rinke de Vries", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X + RIGHT_X_CENTER, CENTER_Y - 150);
	auto* name5 = new Text(8, new ColoredText("William Ross", Color(0, 0, 0), false), SHORT_NAME_WIDTH, TEXT_HEIGHT, CENTER_X + RIGHT_X_CENTER, CENTER_Y + 50);
	auto* name6 = new Text(9, new ColoredText("Wouter van Hees", Color(0, 0, 0), false), LONG_NAME_WIDTH, TEXT_HEIGHT, CENTER_X + RIGHT_X_CENTER, CENTER_Y + 250);
	auto* name7 = new Text(10, new ColoredText("Foxtrot", Color(0, 0, 0), false), 500, 75, CENTER_X - 350, CENTER_Y + 650);
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
	auto* backBtn = new SecondaryButton(3, "To Main Menu", BIND_FN(onBackClick), this->dispatcher);
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	addNewObjectToLayer(5, backBtn);
}

/// @brief 
/// Create the background for this scene
void CreditsScene::loadBackground() {
	SpriteObject* bg = new SpriteObject(-1012, 1080, 1920, 1, 300, "Assets/Backgrounds/credits_foreground.png");
	auto* bgLayer = new Drawable(13);
	bgLayer->setStatic(true);
	bgLayer->setPositionX(0);
	bgLayer->setPositionY(1080);
	bgLayer->setWidth(1920);
	bgLayer->setHeight(1080);
	bgLayer->registerSprite(SpriteState::DEFAULT, bg);
	bgLayer->changeToState(SpriteState::DEFAULT);

	SpriteObject* fgTop = new SpriteObject(-1010, 1080, 1920, 1, 300, "Assets/Backgrounds/credits_foreground_top.png");

	auto* foregroundTop = new Drawable(14);
	foregroundTop->setStatic(true);
	foregroundTop->setPositionX(0);
	foregroundTop->setPositionY(0 + 250);
	foregroundTop->setWidth(1920);
	foregroundTop->setHeight(250);
	foregroundTop->registerSprite(SpriteState::DEFAULT, fgTop);
	foregroundTop->changeToState(SpriteState::DEFAULT);

	SpriteObject* BG_LAYER_1 = new SpriteObject(-1011, 1080, 1920, 1, 300, "Assets/Backgrounds/credits_foreground_bottom.png");

	auto* foregroundBottom = new Drawable(15);
	foregroundBottom->setStatic(true);
	foregroundBottom->setPositionX(0);
	foregroundBottom->setPositionY(1080);
	foregroundBottom->setWidth(1920);
	foregroundBottom->setHeight(250);
	foregroundBottom->registerSprite(SpriteState::DEFAULT, BG_LAYER_1);
	foregroundBottom->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, bgLayer, false, true);
	addNewObjectToLayer(4, foregroundTop, false, true);
	addNewObjectToLayer(4, foregroundBottom, false, true);
}

/// @brief 
/// Load the sounds for this scene
void CreditsScene::loadMusic() {
	engine.soundEngine.onLoadBackgroundMusicEvent("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav");
}

/// @brief 
/// Create the sounds for this scene
void CreditsScene::start()
{
	engine.soundEngine.onStartBackgroundMusicEvent("WIN_SOUND");
}

void CreditsScene::onUpdate()
{
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
	engine.soundEngine.onStartBackgroundMusicEvent("WIN_SOUND");
	Scene::onDetach();
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworl
void CreditsScene::onBackClick() {
	stateMachine.switchToScene("MainMenu", false);
}

void CreditsScene::empty() { }