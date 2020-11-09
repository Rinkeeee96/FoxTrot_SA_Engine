#include "MainMenu.h"
#include "stdafx.h"
#include "Events/Mouse/MousePressed.h"
#include "Events/EventSingleton.h"
#include "Events/Video/VideoLoadSpriteEvent.h"
#include "SpriteState.h"
#include <Engine\Events\Sound\SoundAttachEvent.h>
#include <Engine\Events\Sound\OnMusicStartEvent.h>
#include <Engine\Events\Sound\OnMusicStopEvent.h>

#define BIND_FN(function) std::bind(&MainMenu::function, *this)
#define CENTER_X  1920 / 2
#define CENTER_Y 1080 / 2

void MainMenu::OnAttach()
{
	Button* startBtn = new Button(1, "start", Color(0, 0, 0), BIND_FN(OnStartBtnClick));
	
	startBtn->setSize(100, 50);
	startBtn->registerSprite(SpriteState::DEFAULT, new SpriteObject(1, 34, 10, 1, 300, "Assets/Buttons/btn_green_large.png"));
	startBtn->changeToState(SpriteState::DEFAULT);
	startBtn->setPositionX(CENTER_X);
	startBtn->setPositionY(CENTER_Y);

	addNewObjectToLayer(3, startBtn);

	LoadBackground();
	LoadMusic();

}

void MainMenu::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(1000, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(1001, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(1002, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	Object* layer0 = new Object(1);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	Object* animation = new Object(2);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);

	Object* layer2 = new Object(3);
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
}

void MainMenu::OnStartBtnClick()
{
	cout << "clickeroo" << endl;
}
