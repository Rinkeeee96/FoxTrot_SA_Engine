#include "pch.h"
#include "CreditsScene.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"

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
	backBtn = new SecondaryButton(3, "To Main Menu", BIND_FN(onBackClick));
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	auto* name1 = new PrimaryButton(4, "Lars Jansen", BIND_FN(empty));
	name1->setPositionX(CENTER_X - name1->getWidth() - 200);
	name1->setPositionY(CENTER_Y - name1->getHeight() - 100);
	name1->disable();

	auto* name2 = new PrimaryButton(5, "Max van Nistelrooij", BIND_FN(empty));
	name2->setPositionX(CENTER_X - name2->getWidth() - 200);
	name2->setPositionY(CENTER_Y - name2->getHeight() + 100);
	name2->disable();

	auto* name3 = new PrimaryButton(6, "Rinke de Vries", BIND_FN(empty));
	name3->setPositionX(CENTER_X - name3->getWidth() - 200);
	name3->setPositionY(CENTER_Y - name3->getHeight() + 300);
	name3->disable();


	auto* name4 = new PrimaryButton(7, "Thijs de leeuw", BIND_FN(empty));
	name4->setPositionX(CENTER_X + name4->getWidth() /2 + 100);
	name4->setPositionY(CENTER_Y - name4->getHeight() - 100);
	name4->disable();

	auto* name5 = new PrimaryButton(8, "William Ross", BIND_FN(empty));
	name5->setPositionX(CENTER_X + name5->getWidth() /2 + 100);
	name5->setPositionY(CENTER_Y - name5->getHeight() + 100);
	name5->disable();

	auto* name6 = new PrimaryButton(9, "Wouter van Hees", BIND_FN(empty));
	name6->setPositionX(CENTER_X + name6->getWidth() /2 + 100);
	name6->setPositionY(CENTER_Y - name6->getHeight() + 300);
	name6->disable();



	//addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, backBtn);
	addNewObjectToLayer(3, name1);
	addNewObjectToLayer(3, name2);
	addNewObjectToLayer(3, name3);
	addNewObjectToLayer(3, name4);
	addNewObjectToLayer(3, name5);
	addNewObjectToLayer(3, name6);
}

/// @brief 
/// Create the background for this scene
void CreditsScene::loadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-1010, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");

	auto* layer0 = new Drawable(-602);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0);
}

/// @brief 
/// Load the sounds for this scene
void CreditsScene::loadMusic() {
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("DEAD_SOUND", "Assets/Sound/game_over_looped.wav"));
}

/// @brief 
/// Create the sounds for this scene
void CreditsScene::start()
{
	backBtn->reset();
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("DEAD_SOUND"));
}

void CreditsScene::onUpdate()
{
}

/// @brief 
/// Remove the sounds of the soundengine
void CreditsScene::onDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("DEAD_SOUND"));
	Scene::onDetach();
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworl
void CreditsScene::onBackClick() {
	SceneSwitcher::get_instance().switchToScene("MAIN_MENU", false);
}

void CreditsScene::empty() { }