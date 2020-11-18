#include "pch.h"
#include "MainMenu.h"
#include "stdafx.h"
#include "Events/Mouse/MousePressed.h"
#include "Events/EventSingleton.h"
#include "Events/Video/VideoLoadSpriteEvent.h"
#include "../SpriteState.h"
#include <Engine\Events\Sound\SoundAttachEvent.h>
#include <Engine\Events\Sound\OnMusicStartEvent.h>
#include <Engine\Events\Sound\OnMusicStopEvent.h>
#include <Engine\Events\Window\WindowCloseEvent.h>
#include "../Buttons/PrimaryButton.h"
#include "../Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&MainMenu::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void MainMenu::OnAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

void MainMenu::LoadButtons() {

	Button* startBtn = new PrimaryButton(10, "Start", BIND_FN(OnStartBtnClick));
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);

	Button* loadBtn = new PrimaryButton(11, "Win screen", BIND_FN(OnLoadBtnClick));
	loadBtn->setPositionX(CENTER_X - loadBtn->getWidth() / 2);
	loadBtn->setPositionY(CENTER_Y - loadBtn->getHeight() / 2 + 100);

	Button* creditsBtn = new PrimaryButton(12, "Game over screen", BIND_FN(OnCreditsBtnClick));
	creditsBtn->setPositionX(CENTER_X - creditsBtn->getWidth() / 2);
	creditsBtn->setPositionY(CENTER_Y - creditsBtn->getHeight() / 2 + 200);

	Button* stopBtn = new SecondaryButton(13, "Stop", BIND_FN(OnStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, stopBtn);
	addNewObjectToLayer(3, loadBtn);
	addNewObjectToLayer(3, creditsBtn);
}

void MainMenu::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(1010, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(1011, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(1012, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(14);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(15);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(16);
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
void MainMenu::LoadMusic() {
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav"));
}
void MainMenu::Start()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("MENU_SOUND"));
}

void MainMenu::OnDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("MENU_SOUND"));
	Scene::OnDetach();
}

void MainMenu::OnStartBtnClick()
{
	SceneSwitcher::get_instance().SwitchToScene("GAME");
}

void MainMenu::OnStopBtnClick() {
	WindowCloseEvent event;
	EventSingleton::get_instance().dispatchEvent<WindowCloseEvent>(event);
}

void MainMenu::OnCreditsBtnClick() {
	SceneSwitcher::get_instance().SwitchToScene("DEAD_SCREEN");
}

void MainMenu::OnLoadBtnClick() {
	SceneSwitcher::get_instance().SwitchToScene("WIN_SCREEN");
}
