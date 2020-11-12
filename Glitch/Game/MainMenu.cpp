#include "MainMenu.h"
#include "stdafx.h"
#include "Events/Mouse/MousePressed.h"
#include "Events/EventSingleton.h"
#include "Events/Video/VideoLoadSpriteEvent.h"
#include "SpriteState.h"
#include <Engine\Events\Sound\SoundAttachEvent.h>
#include <Engine\Events\Sound\OnMusicStartEvent.h>
#include <Engine\Events\Sound\OnMusicStopEvent.h>
#include <Engine\Events\Window\WindowCloseEvent.h>

#define BIND_FN(function) std::bind(&MainMenu::function, *this)
#define MAX_X 1920
#define MAX_Y 1080

#define CENTER_X  (MAX_X / 2)
#define CENTER_Y (MAX_Y / 2)

void MainMenu::OnAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

void MainMenu::LoadButtons() {
	auto mainSprite = new SpriteObject(1, 40, 116, 1, 300, "Assets/Buttons/btn_green_round.png");
	Color black = Color(0, 0, 0);

	Button startBtn(1, ColoredString("Start", black), BIND_FN(OnStartBtnClick));
	startBtn.setSize(200, 50);
	startBtn.registerSprite(SpriteState::DEFAULT, mainSprite);
	startBtn.changeToState(SpriteState::DEFAULT);
	startBtn.setPositionX(CENTER_X - startBtn.getWidth() / 2);
	startBtn.setPositionY(CENTER_Y - startBtn.getHeight() / 2);

	Button stopBtn(2, ColoredString("Stop", black), BIND_FN(OnStopBtnClick));
	stopBtn.registerSprite(SpriteState::DEFAULT, new SpriteObject(2, 40, 116, 1, 300, "Assets/Buttons/btn_red_round.png"));
	stopBtn.changeToState(SpriteState::DEFAULT);
	stopBtn.setPositionX(MAX_X - 40 - stopBtn.getWidth());
	stopBtn.setPositionY(MAX_Y - 10 - stopBtn.getHeight());

	Button loadBtn(3, ColoredString("Load", black), BIND_FN(OnLoadBtnClick));
	loadBtn.registerSprite(SpriteState::DEFAULT, mainSprite);
	loadBtn.changeToState(SpriteState::DEFAULT);
	loadBtn.setPositionX(CENTER_X - loadBtn.getWidth() / 2);
	loadBtn.setPositionY(CENTER_Y - loadBtn.getHeight() / 2 + 100);
	loadBtn.disable();

	Button creditsBtn(4, ColoredString("Credits", black), BIND_FN(OnCreditsBtnClick));
	creditsBtn.registerSprite(SpriteState::DEFAULT, mainSprite);
	creditsBtn.changeToState(SpriteState::DEFAULT);
	creditsBtn.setPositionX(CENTER_X - creditsBtn.getWidth() / 2);
	creditsBtn.setPositionY(CENTER_Y - creditsBtn.getHeight() / 2 + 200);
	creditsBtn.disable();

	addNewObjectToLayer(3, &startBtn);
	addNewObjectToLayer(3, &stopBtn);
	addNewObjectToLayer(3, &loadBtn);
	addNewObjectToLayer(3, &creditsBtn);
}

void MainMenu::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(1000, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(1001, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(1002, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(1);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(2);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);

	auto* layer2 = new Drawable(3);
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
	cout << "Start BTN" << endl;
}

void MainMenu::OnStopBtnClick() {
	auto event = WindowCloseEvent();
	EventSingleton::get_instance().dispatchEvent<WindowCloseEvent>(event);
}

void MainMenu::OnCreditsBtnClick() {
	cout << "Start Credit" << endl;
}

void MainMenu::OnLoadBtnClick() {
	cout << "Start Load game BTN" << endl;
}