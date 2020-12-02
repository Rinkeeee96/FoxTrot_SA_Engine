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
	loadBackground();
	loadMusic();
}

/// @brief 
/// Create all buttons for this scene
void CreditsScene::loadButtons() {
	// Back button
	auto* backBtn = new SecondaryButton(3, "To Main Menu", BIND_FN(onBackClick), this->dispatcher);
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());
	backBtn = new SecondaryButton(3, "To Main Menu", BIND_FN(onBackClick), this->dispatcher);
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	auto* name1 = new Text(4, new ColoredText("Lars Jansen", Color(255, 255, 255)), 300, 50, CENTER_X - 500, CENTER_Y - 150);
	auto* name2 = new Text(5, new ColoredText("Max van Nistelrooij", Color(255, 255, 255)), 350, 50, CENTER_X - 500, CENTER_Y + 50);
	auto* name3 = new Text(6, new ColoredText("Rinke de Vries", Color(255, 255, 255)), 300, 50, CENTER_X - 500, CENTER_Y + 250);

	auto* name4 = new Text(7, new ColoredText("Thijs de leeuw", Color(255, 255, 255)), 300, 50, CENTER_X + 50, CENTER_Y - 150);
	auto* name5 = new Text(8, new ColoredText("William Ross", Color(255, 255, 255)), 300, 50, CENTER_X + 50, CENTER_Y + 50);
	auto* name6 = new Text(9, new ColoredText("Wouter van Hees", Color(255, 255, 255)), 350, 50, CENTER_X + 50, CENTER_Y + 250);

	//addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, backBtn);
	addNewObjectToLayer(3, name1);
	addNewObjectToLayer(3, name2);
	addNewObjectToLayer(3, name3);
	addNewObjectToLayer(3, name4);
	addNewObjectToLayer(3, name5);
	addNewObjectToLayer(3, name6);

	this->text.push_back(name1);
	this->text.push_back(name2);
	this->text.push_back(name3);
	this->text.push_back(name4);
	this->text.push_back(name5);
	this->text.push_back(name6);
}

/// @brief 
/// Create the background for this scene
void CreditsScene::loadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-1010, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");

	auto* layer0 = new Drawable(14);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
}

/// @brief 
/// Load the sounds for this scene
void CreditsScene::loadMusic() {
	engine.soundEngine.onLoadBackgroundMusicEvent("DEAD_SOUND", "Assets/Sound/game_over_looped.wav");
}

/// @brief 
/// Create the sounds for this scene
void CreditsScene::start()
{
	engine.soundEngine.onStartBackgroundMusicEvent("DEAD_SOUND");
}

void CreditsScene::onUpdate()
{
	for (size_t i = 0; i < this->text.size(); i++)
	{
		this->text[i]->setPositionY(this->text[i]->getPositionY() - 1);

		if (text[i]->getPositionY() == 0) {
			this->text[i]->setPositionY(WINDOW_HEIGHT);
		}
	}
}

/// @brief 
/// Remove the sounds of the soundengine
void CreditsScene::onDetach()
{
	engine.soundEngine.onStartBackgroundMusicEvent("DEAD_SOUND");
	Scene::onDetach();
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworl
void CreditsScene::onBackClick() {
	stateMachine.switchToScene("MainMenu", false);
}

void CreditsScene::empty() { }