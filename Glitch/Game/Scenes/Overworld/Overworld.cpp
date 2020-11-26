#include "pch.h"
#include "Overworld.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&Overworld::function, *this)

/// @brief 
/// Loadbuttons
/// LoadBackground
/// LoadMusic
void Overworld::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

/// @brief 
/// Loads all the buttons in the Overworld
void Overworld::loadButtons() {
	auto defaultBtnSprite = new SpriteObject(101013, 11, 15, 1, 300, "Assets/Buttons/village_orange.png");
	auto hoverBtnSprite = new SpriteObject(101012, 11, 15, 1, 300, "Assets/Buttons/village_gray.png");
	level1Btn = new Button(1, ColoredText("", Color(255, 255, 255)), BIND_FN(onLevel1BtnClick), defaultBtnSprite);
	level1Btn->setWidth(32);
	level1Btn->setHeight(32);
	level1Btn->setPositionX(795);
	level1Btn->setPositionY(840); 
	level1Btn->registerHoverSprite(hoverBtnSprite);


	level2Btn = new Button(2, ColoredText("", Color(255, 255, 255)), BIND_FN(onLevel1BtnClick), defaultBtnSprite);
	level2Btn->setWidth(100);
	level2Btn->setHeight(100);
	level2Btn->setPositionX(900);
	level2Btn->setPositionY(740);
	level2Btn->registerHoverSprite(hoverBtnSprite);

	/*
	Button* level2Btn = new PrimaryButton(2, "Level 2", BIND_FN(OnLevel2BtnClick));
	level2Btn->setPositionX(710);
	level2Btn->setPositionY(890);
	*/
	stopBtn = new SecondaryButton(3, "To Main Menu", BIND_FN(onStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, level1Btn);
	addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, stopBtn);
}

/// @brief 
/// Loads the background
void Overworld::loadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-9123, 1440, 1344, 1, 1, "Assets/Overworld/World.png");

	auto* layer0 = new Drawable(1);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);
	layer0->setScalable(false);

	addNewObjectToLayer(1, layer0);
}

/// @brief 
void Overworld::loadMusic() {
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("OVER_WORLD", "Assets/Sound/file_example_WAV_1MG.wav"));
}

/// @brief 
void Overworld::start()
{
	level1Btn->reset();
	stopBtn->reset();
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("OVER_WORLD"));
}

/// @brief 
void Overworld::onUpdate()
{
}

/// @brief 
void Overworld::onDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("OVER_WORLD"));
	Scene::onDetach();
}

/// @brief 
void Overworld::onLevel1BtnClick()
{
	cout << "Level1 BTN" << endl;
	SceneSwitcher::get_instance().switchToScene("LEVEL_1", true);
}

/// @brief 
void Overworld::onLevel2BtnClick()
{
	cout << "Level2 BTN" << endl;
}

/// @brief 
void Overworld::onStartBtnClick()
{
	cout << "Start BTN" << endl;
}

/// @brief 
void Overworld::onStopBtnClick() {
	SceneSwitcher::get_instance().switchToScene("MAIN_MENU",true);
}

/// @brief 
void Overworld::onCreditsBtnClick() {
	cout << "Start Credit" << endl;
}

/// @brief 
void Overworld::onLoadBtnClick() {
	cout << "Start Load game BTN" << endl;
}
