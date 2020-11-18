#include "pch.h"
#include "MainMenu.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&MainMenu::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void MainMenu::OnAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

/// @brief 
/// Create all buttons for this scene
void MainMenu::LoadButtons() {

	Button* startBtn = new PrimaryButton(1, "Start", BIND_FN(OnStartBtnClick));
	startBtn->setPositionX(CENTER_X - startBtn->getWidth() / 2);
	startBtn->setPositionY(CENTER_Y - startBtn->getHeight() / 2);

	Button* loadBtn = new PrimaryButton(3, "Load", BIND_FN(OnLoadBtnClick));
	loadBtn->setPositionX(CENTER_X - loadBtn->getWidth() / 2);
	loadBtn->setPositionY(CENTER_Y - loadBtn->getHeight() / 2 + 100);
	loadBtn->disable();

	Button* creditsBtn = new PrimaryButton(4, "Credits", BIND_FN(OnCreditsBtnClick));
	creditsBtn->setPositionX(CENTER_X - creditsBtn->getWidth() / 2);
	creditsBtn->setPositionY(CENTER_Y - creditsBtn->getHeight() / 2 + 200);
	creditsBtn->disable();

	Button* stopBtn = new SecondaryButton(2, "Stop", BIND_FN(OnStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, startBtn);
	addNewObjectToLayer(3, stopBtn);
	addNewObjectToLayer(3, loadBtn);
	addNewObjectToLayer(3, creditsBtn);
}

/// @brief 
/// Create the background for this scene
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
	animation->setScalable(false);

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

/// @brief 
/// Load the sounds for this scene
void MainMenu::LoadMusic() {
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav"));
}

/// @brief 
/// Create the sounds for this scene
void MainMenu::Start()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("MENU_SOUND"));
}

/// @brief 
/// Remove the sounds of the soundengine
void MainMenu::OnDetach()
{
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("MENU_SOUND"));
	Scene::OnDetach();
}

/// @brief 
/// A callback function for startBTN
/// Start transition scene to overworld
void MainMenu::OnStartBtnClick()
{
	SceneSwitcher::get_instance().SwitchToScene("GENERAL_TRANSITION_SCENE");
	cout << "Start BTN" << endl;
}

/// @brief 
/// A callback function for stopBTN
void MainMenu::OnStopBtnClick() {
	WindowCloseEvent event;
	EventSingleton::get_instance().dispatchEvent<WindowCloseEvent>(event);
}

/// @brief 
/// A callback function for creditsBTN
void MainMenu::OnCreditsBtnClick() {
	cout << "Start Credit" << endl;
}

/// @brief 
/// A callback function for loadBTN
void MainMenu::OnLoadBtnClick() {
	cout << "Start Load game BTN" << endl;
}

void MainMenu::update()
{

}
