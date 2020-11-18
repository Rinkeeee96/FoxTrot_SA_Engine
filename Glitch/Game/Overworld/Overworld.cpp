#include "pch.h"
#include "Overworld.h"

#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&Overworld::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

/// @brief 
/// Loadbuttons
/// LoadBackground
/// LoadMusic
void Overworld::OnAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

/// @brief 
/// Loads all the buttons in the Overworld
void Overworld::LoadButtons() {

	Button* level1Btn = new PrimaryButton(1, "Level 1", BIND_FN(OnLevel1BtnClick));
	level1Btn->setPositionX(280);
	level1Btn->setPositionY(1060);

	Button* level2Btn = new PrimaryButton(2, "Level 2", BIND_FN(OnLevel2BtnClick));
	level2Btn->setPositionX(710);
	level2Btn->setPositionY(890);

	Button* stopBtn = new SecondaryButton(3, "Stop", BIND_FN(OnStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, level1Btn);
	addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, stopBtn);
}

/// @brief 
/// Loads the background
void Overworld::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(1010, 1440, 1344, 1, 1, "Assets/Overworld/World.png");

	auto* layer0 = new Drawable(1);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);
	layer0->setScalable(false);

	addNewObjectToLayer(0, layer0);
}

/// @brief 
void Overworld::LoadMusic() {

}

/// @brief 
void Overworld::Start()
{

}

/// @brief 
void Overworld::update()
{
}

/// @brief 
void Overworld::OnDetach()
{
	Scene::OnDetach();
}

/// @brief 
void Overworld::OnLevel1BtnClick()
{
	cout << "Level1 BTN" << endl;
	SceneSwitcher::get_instance().SwitchToScene("GAME");
}

/// @brief 
void Overworld::OnLevel2BtnClick()
{
	cout << "Level2 BTN" << endl;
}

/// @brief 
void Overworld::OnStartBtnClick()
{
	cout << "Start BTN" << endl;
}

/// @brief 
void Overworld::OnStopBtnClick() {
	SceneSwitcher::get_instance().SwitchToScene("MAIN_MENU");
}

/// @brief 
void Overworld::OnCreditsBtnClick() {
	cout << "Start Credit" << endl;
}

/// @brief 
void Overworld::OnLoadBtnClick() {
	cout << "Start Load game BTN" << endl;
}
