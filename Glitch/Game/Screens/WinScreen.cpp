#include "pch.h"
#include "WinScreen.h"
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

#define BIND_FN(function) std::bind(&WinScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void WinScreen::OnAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

void WinScreen::LoadButtons() {
	auto mainSprite = new SpriteObject(1031, 40, 116, 1, 300, "Assets/Buttons/btn_gray_round.png");

	Button* overBtn = new Button(31, ColoredText("Overworld", Color(0, 0, 0)), BIND_FN(OnStartBtnClick));
	overBtn->setPositionX(CENTER_X - overBtn->getWidth() / 2);
	overBtn->setPositionY(CENTER_Y - overBtn->getHeight() / 2);
	overBtn->setSize(200, 50);
	overBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	overBtn->changeToState(SpriteState::DEFAULT);

	Button* saveBtn = new Button(32, ColoredText("Opslaan", Color(0, 0, 0)), BIND_FN(OnMainBtnClick));
	saveBtn->setPositionX(CENTER_X - saveBtn->getWidth() / 2);
	saveBtn->setPositionY(CENTER_Y - saveBtn->getHeight() / 2 + 100);
	saveBtn->setSize(200, 50);
	saveBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	saveBtn->changeToState(SpriteState::DEFAULT);

	Button* mainBtn = new Button(33, ColoredText("Hoofdmenu", Color(0, 0, 0)), BIND_FN(OnMainBtnClick));
	mainBtn->setPositionX(CENTER_X - mainBtn->getWidth() / 2);
	mainBtn->setPositionY(CENTER_Y - mainBtn->getHeight() / 2 + 200);
	mainBtn->setSize(200, 50);
	mainBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	mainBtn->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(3, overBtn);
	addNewObjectToLayer(3, mainBtn);
}

void WinScreen::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(1031, 1080, 1920, 1, 300, "Assets/Backgrounds/game_over_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(1032, 37, 50, 7, 300, "Assets/Sprites/Character/adventure_die.png");
	BG_LAYER_ADVENTRUE->freezeOn(7);
	SpriteObject* BG_LAYER_2 = new SpriteObject(1032, 1080, 1920, 1, 300, "Assets/Backgrounds/game_over_Layer_1.png");

	auto* layer0 = new Drawable(34);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(35);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(36);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0);
	addNewObjectToLayer(1, animation);
	//addNewObjectToLayer(2, layer2);
}

void WinScreen::LoadMusic() {

	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("APPLAUSE_SOUND", "Assets/Sound/applause.wav"));
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav"));
}

void WinScreen::Start()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("WIN_SOUND"));
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("APPLAUSE_SOUND"));
}

void WinScreen::OnDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("APPLAUSE_SOUND"));
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("WIN_SOUND"));
}

void WinScreen::OnStartBtnClick()
{
	SceneSwitcher::get_instance().SwitchToScene("GAME");
	cout << "Start BTN" << endl;
}

void WinScreen::OnMainBtnClick() {
	cout << "Start BTN" << endl;
	SceneSwitcher::get_instance().SwitchToScene("MAIN_MENU");
}
