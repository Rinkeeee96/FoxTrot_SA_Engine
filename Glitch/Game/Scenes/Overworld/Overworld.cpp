#include "pch.h"
#include "Overworld.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

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
	auto transSprite = new SpriteObject(101014, 10, 10, 1, 300, "Assets/transparant.png");

	auto* level1Btn = new Button(1, ColoredText("", Color(255, 255, 255)), BIND_FN(onLevel1BtnClick), defaultBtnSprite, this->dispatcher);
	level1Btn->setWidth(32);
	level1Btn->setHeight(32);
	level1Btn->setPositionX(295);
	level1Btn->setPositionY(363);
	level1Btn->registerHoverSprite(hoverBtnSprite);

	auto* level1TextBtn = new Button(2, ColoredText("Level 1, Score: " + to_string(savegame->getCurrentGameData().levelData[0].score), Color(0, 0, 0)), BIND_FN(onLevel1BtnClick), transSprite, this->dispatcher);
	level1TextBtn->setWidth(32);
	level1TextBtn->setHeight(20);
	level1TextBtn->setPositionX(295);
	level1TextBtn->setPositionY(383);

	auto* level2Btn = new Button(3, ColoredText("", Color(255, 255, 255)), BIND_FN(onLevel2BtnClick), defaultBtnSprite, this->dispatcher);
	level2Btn->setWidth(32);
	level2Btn->setHeight(32);
	level2Btn->setPositionX(955);
	level2Btn->setPositionY(320);
	level2Btn->registerHoverSprite(hoverBtnSprite);

	string level2Name = "Locked";
	if (savegame->getCurrentGameData().levelData[0].completed)
	{
		level2Name = "Level 2, Score: " + to_string(savegame->getCurrentGameData().levelData[1].score);
	}
	auto* level2TextBtn = new Button(4, ColoredText(level2Name, Color(0, 0, 0)), BIND_FN(onLevel2BtnClick), transSprite, this->dispatcher);
	level2TextBtn->setWidth(32);
	level2TextBtn->setHeight(20);
	level2TextBtn->setPositionX(955);
	level2TextBtn->setPositionY(340);
	if (!savegame->getCurrentGameData().levelData[0].completed)
	{
		level2Btn->disable();
		level2TextBtn->disable();
	}

	string level3Name = "Locked";
	if (savegame->getCurrentGameData().levelData[1].completed)
	{
		level3Name = "Level 3, Score: " + to_string(savegame->getCurrentGameData().levelData[2].score);
	}
    auto* level3Btn = new Button(5, ColoredText("", Color(255, 255, 255)), BIND_FN(onLevel3BtnClick), defaultBtnSprite, this->dispatcher);
	level3Btn->setWidth(32);
	level3Btn->setHeight(32);
	level3Btn->setPositionX(795);
	level3Btn->setPositionY(850);
	level3Btn->registerHoverSprite(hoverBtnSprite);

	auto* level3TextBtn = new Button(6, ColoredText(level3Name, Color(0, 0, 0)), BIND_FN(onLevel3BtnClick), transSprite, this->dispatcher);
	level3TextBtn->setWidth(32);
	level3TextBtn->setHeight(20);
	level3TextBtn->setPositionX(795);
	level3TextBtn->setPositionY(870);
	if (!savegame->getCurrentGameData().levelData[1].completed)
	{
		level3Btn->disable();
		level3TextBtn->disable();
	}

	auto* stopBtn = new SecondaryButton(7, "To Main Menu", BIND_FN(onStopBtnClick), this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, level1Btn);
	addNewObjectToLayer(3, level1TextBtn);
	addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, level2TextBtn);
	addNewObjectToLayer(3, level3Btn);
	addNewObjectToLayer(3, level3TextBtn);
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

	addNewObjectToLayer(1, layer0, false, true);
}

/// @brief 
void Overworld::loadMusic() {
	engine.soundEngine.onLoadBackgroundMusicEvent("OVER_WORLD", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
void Overworld::start(bool playSound)
{
	if(playSound)engine.soundEngine.onStartBackgroundMusicEvent("OVER_WORLD");
}

/// @brief 
void Overworld::onUpdate()
{
}

/// @brief 
void Overworld::onDetach()
{
	engine.soundEngine.onStartBackgroundMusicEvent("OVER_WORLD");
	Scene::onDetach();
}

/// @brief 
void Overworld::onLevel1BtnClick()
{
	cout << "Level1 BTN" << endl;
	stateMachine.switchToScene("Level_1", true);
}

/// @brief 
void Overworld::onLevel2BtnClick()
{
	cout << "Level2 BTN" << endl;
	stateMachine.switchToScene("Level_2", true);
}

/// @brief 
void Overworld::onLevel3BtnClick()
{
	cout << "Level3 BTN" << endl;
	stateMachine.switchToScene("Level_3", true);
}

/// @brief 
void Overworld::onStartBtnClick()
{
	cout << "Start BTN" << endl;
}

/// @brief 
void Overworld::onStopBtnClick() {
	stateMachine.switchToScene("MainMenu",true);
}

/// @brief 
void Overworld::onCreditsBtnClick() {
	cout << "Start Credit" << endl;
}

/// @brief 
void Overworld::onLoadBtnClick() {
	cout << "Start Load game BTN" << endl;
}
