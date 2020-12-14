#include "pch.h"
#include "ChapterOneScene.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)
#define BIND_FN(function) std::bind(&ChapterOneScene::function, *this)

/// @brief Loads al the text, buttons and background for this scene
void ChapterOneScene::onAttach()
{
	loadButtons();
	loadText();
	loadBackground();
	loadMusic();
}

/// @brief 
/// Create all text for this scene
void ChapterOneScene::loadText() {
	this->setTextFromFile("Assets/Levels/Story/ChapterOne.txt", 4);

	for (size_t i = 0; i < this->text.size(); i++)
	{
		addNewObjectToLayer(2, this->text[i], false, true);
	}
}

/// @brief 
/// Create the background for this scene
void ChapterOneScene::loadBackground() {
	SpriteObject* background = new SpriteObject(-33, 1080, 1920, 1, 300, "Assets/Backgrounds/dark_bg.png");
	auto* backgroundLayer = new Drawable(0);
	backgroundLayer->setStatic(true);
	backgroundLayer->setPositionX(0);
	backgroundLayer->setPositionY(1080);
	backgroundLayer->setWidth(1920);
	backgroundLayer->setHeight(1080);
	backgroundLayer->registerSprite(SpriteState::DEFAULT, background);
	backgroundLayer->changeToState(SpriteState::DEFAULT);

	SpriteObject* foregroundBottom = new SpriteObject(-34, 1080, 1920, 1, 300, "Assets/Backgrounds/foreground_bottom.png");
	auto* foregroundBottomLayer = new Drawable(1);
	foregroundBottomLayer->setStatic(true);
	foregroundBottomLayer->setPositionX(0);
	foregroundBottomLayer->setPositionY(1080);
	foregroundBottomLayer->setWidth(1920);
	foregroundBottomLayer->setHeight(176);
	foregroundBottomLayer->registerSprite(SpriteState::DEFAULT, foregroundBottom);
	foregroundBottomLayer->changeToState(SpriteState::DEFAULT);

	SpriteObject* foregroundTop = new SpriteObject(-35, 1080, 1920, 1, 300, "Assets/Backgrounds/foreground_top.png");
	auto* foregroundTopLayer = new Drawable(2);
	foregroundTopLayer->setStatic(true);
	foregroundTopLayer->setPositionX(0);
	foregroundTopLayer->setPositionY(124);
	foregroundTopLayer->setWidth(1920);
	foregroundTopLayer->setHeight(124);
	foregroundTopLayer->registerSprite(SpriteState::DEFAULT, foregroundTop);
	foregroundTopLayer->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, backgroundLayer, false, true);
	addNewObjectToLayer(3, foregroundTopLayer, false, true);
	addNewObjectToLayer(3, foregroundBottomLayer, false, true);
}

/// @brief 
/// Load the sounds for this scene
void ChapterOneScene::loadMusic() {
	engine->loadSound("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav");
}

/// @brief 
/// Create the sounds for this scene
void ChapterOneScene::start(bool playSound)
{
	if (playSound)engine->startSound("WIN_SOUND");
	this->speed_ = 1;
}

/// @brief 
/// Remove the sounds of the soundengine
void ChapterOneScene::onDetach()
{
	engine->startSound("WIN_SOUND");
	ChapterScene::onDetach();
}