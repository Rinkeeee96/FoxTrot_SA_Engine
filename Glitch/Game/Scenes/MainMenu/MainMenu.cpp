#include "pch.h"
#include "MainMenu.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&MainMenu::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void MainMenu::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

/// @brief 
/// Create all buttons for this scene
void MainMenu::loadButtons() {

	Button* startBtn = new PrimaryButton(10, "Start", BIND_FN(onStartBtnClick));
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);

	
	Button* loadBtn = new PrimaryButton(3, "Win screen", BIND_FN(onLoadBtnClick));
	loadBtn->setPositionX(CENTER_X - loadBtn->getWidth() / 2);
	loadBtn->setPositionY(CENTER_Y - loadBtn->getHeight() / 2 + 100);

	Button* creditsBtn = new PrimaryButton(12, "Game over screen", BIND_FN(onCreditsBtnClick));
	creditsBtn->setPositionX(CENTER_X - creditsBtn->getWidth() / 2);
	creditsBtn->setPositionY(CENTER_Y - creditsBtn->getHeight() / 2 + 200);
	creditsBtn->disable();

	Button* stopBtn = new SecondaryButton(13, "Stop", BIND_FN(onStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, stopBtn);
	addNewObjectToLayer(3, loadBtn);
	addNewObjectToLayer(3, creditsBtn);
}

/// @brief 
/// Create the background for this scene
void MainMenu::loadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-9005, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-9006, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-9007, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

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

	addNewObjectToLayer(0, layer0, false);
	addNewObjectToLayer(1, animation, false);
	addNewObjectToLayer(2, layer2, false);
}

/// @brief 
/// Load the sounds for this scene
void MainMenu::loadMusic() {
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav"));
}

/// @brief 
/// Create the sounds for this scene
void MainMenu::start()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("MENU_SOUND"));
}

void MainMenu::onUpdate()
{
}

/// @brief 
/// Remove the sounds of the soundengine
void MainMenu::onDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("MENU_SOUND"));
	Scene::onDetach();
}


/// @brief 
/// A callback function for startBtn
/// Start transition scene to OVERWORLD
void MainMenu::onStartBtnClick()
{
	SceneSwitcher::get_instance().switchToScene("OVERWORLD", true);
}


/// @brief 
/// A callback function for stopBTN
/// Stop the application
void MainMenu::onStopBtnClick() {
	WindowCloseEvent event;
	EventSingleton::get_instance().dispatchEvent<WindowCloseEvent>(event);
}


/// @brief 
/// A callback function for creditsBTN
/// Start transition scene to DEAD_SCREEN
void MainMenu::onCreditsBtnClick() {
	SceneSwitcher::get_instance().switchToScene("DEAD_SCREEN", false);
}


/// @brief 
/// A callback function for loadBtn
/// Start transition scene to WIN_SCREEN
void MainMenu::onLoadBtnClick() {
	SceneSwitcher::get_instance().switchToScene("WIN_SCREEN", false);
}
