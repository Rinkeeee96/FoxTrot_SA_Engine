#include "pch.h"
#include "ChapterOneScene.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)
#define BIND_FN(function) std::bind(&ChapterOneScene::function, *this)

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
	this->setTextFromFile("Assets/Levels/Story/ChapterOne.txt");

	for (size_t i = 0; i < this->text.size(); i++)
	{
		addNewObjectToLayer(2, this->text[i], false, true);
	}
}

/// @brief 
/// Create the background for this scene
void ChapterOneScene::loadBackground() {
	SpriteObject* bg0 = new SpriteObject(-33, 1080, 1920, 1, 300, "Assets/Backgrounds/dark_bg.png");
	auto* bgLayer0 = new Drawable(0);
	bgLayer0->setStatic(true);
	bgLayer0->setPositionX(0);
	bgLayer0->setPositionY(1080);
	bgLayer0->setWidth(1920);
	bgLayer0->setHeight(1080);
	bgLayer0->registerSprite(SpriteState::DEFAULT, bg0);
	bgLayer0->changeToState(SpriteState::DEFAULT);

	SpriteObject* fgB = new SpriteObject(-34, 1080, 1920, 1, 300, "Assets/Backgrounds/foreground_bottom.png");
	auto* fgBLayer = new Drawable(1);
	fgBLayer->setStatic(true);
	fgBLayer->setPositionX(0);
	fgBLayer->setPositionY(1080);
	fgBLayer->setWidth(1920);
	fgBLayer->setHeight(200);
	fgBLayer->registerSprite(SpriteState::DEFAULT, fgB);
	fgBLayer->changeToState(SpriteState::DEFAULT);

	SpriteObject* fgT = new SpriteObject(-35, 1080, 1920, 1, 300, "Assets/Backgrounds/foreground_top.png");
	auto* fgTLayer = new Drawable(2);
	fgTLayer->setStatic(true);
	fgTLayer->setPositionX(0);
	fgTLayer->setPositionY(100);
	fgTLayer->setWidth(1920);
	fgTLayer->setHeight(100);
	fgTLayer->registerSprite(SpriteState::DEFAULT, fgT);
	fgTLayer->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, bgLayer0, false, true);
	addNewObjectToLayer(3, fgTLayer, false, true);
	addNewObjectToLayer(3, fgBLayer, false, true);
}

/// @brief 
/// Load the sounds for this scene
void ChapterOneScene::loadMusic() {
	engine.soundEngine.onLoadBackgroundMusicEvent("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav");
}

/// @brief 
/// Create the sounds for this scene
void ChapterOneScene::start(bool playSound)
{
	if (playSound)engine.soundEngine.onStartBackgroundMusicEvent("WIN_SOUND");
	this->speed_ = 1;
}

/// @brief 
/// Remove the sounds of the soundengine
void ChapterOneScene::onDetach()
{
	engine.soundEngine.onStartBackgroundMusicEvent("WIN_SOUND");
	Scene::onDetach();
}