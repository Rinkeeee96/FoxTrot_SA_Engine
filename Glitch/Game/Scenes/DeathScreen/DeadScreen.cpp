#include "pch.h"
#include "DeadScreen.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&DeadScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void DeadScreen::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

void DeadScreen::loadButtons() {
	auto mainSprite = new SpriteObject(-601, 40, 116, 1, 300, "Assets/Buttons/btn_gray_round.png");

	Button* startBtn = new Button(-600, ColoredText("Restart", Color(0, 0, 0)), BIND_FN(onStartBtnClick));
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);
	startBtn->setSize(200, 50);
	startBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	startBtn->changeToState(SpriteState::DEFAULT);

	Button* mainBtn = new Button(-601, ColoredText("Hoofdmenu", Color(0, 0, 0)), BIND_FN(onMainBtnClick));
	mainBtn->setPositionX(CENTER_X - mainBtn->getWidth() / 2);
	mainBtn->setPositionY(CENTER_Y - mainBtn->getHeight() / 2 + 100);
	mainBtn->setSize(200, 50);
	mainBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	mainBtn->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, mainBtn);
}

void DeadScreen::loadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-605, 1080, 1920, 1, 300, "Assets/Backgrounds/game_over_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-606, 37, 50, 7, 300, "Assets/Sprites/Character/adventure_die.png");
	BG_LAYER_ADVENTRUE->freezeOn(7);
	SpriteObject* BG_LAYER_2 = new SpriteObject(-607, 1080, 1920, 1, 300, "Assets/Backgrounds/game_over_Layer_1.png");

	auto* layer0 = new Drawable(-602);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(-604);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(-603);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, layer2);
}

void DeadScreen::loadMusic() {
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("DEAD_SOUND", "Assets/Sound/game_over_looped.wav"));
}

void DeadScreen::start()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("DEAD_SOUND"));
}

void DeadScreen::onUpdate()
{
}

void DeadScreen::onDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("DEAD_SOUND"));
	Scene::onDetach();
}

void DeadScreen::onStartBtnClick()
{
	SceneSwitcher::get_instance().switchToScene("GAME", true);
}

void DeadScreen::onMainBtnClick() {
	SceneSwitcher::get_instance().switchToScene("MAIN_MENU", false);
}
