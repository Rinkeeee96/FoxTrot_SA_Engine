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
	loadSaveGame();
}

/// @brief 
/// Loads all the buttons in the Overworld
void Overworld::loadButtons() {
	auto defaultBtnSprite = new SpriteObject(101013, 11, 15, 1, 300, "Assets/Buttons/village_orange.png");
	auto hoverBtnSprite = new SpriteObject(101012, 11, 15, 1, 300, "Assets/Buttons/village_gray.png");
	auto transSprite = new SpriteObject(101014, 10, 10, 1, 300, "Assets/transparant.png");

	auto* shop = new Button(10, ColoredText("", Color(255, 255, 255)), BIND_FN(onShopBtnClick), defaultBtnSprite, this->dispatcher);
	shop->setWidth(32);
	shop->setHeight(32);
	shop->setPositionX(305);
	shop->setPositionY(1000);
	shop->registerHoverSprite(hoverBtnSprite);

	auto* shopText = new Text(15, new ColoredText("Shop", Color(0, 0, 0)), 60, 50, 390, 1000);

	auto* shop1 = new Button(11, ColoredText("", Color(255, 255, 255)), BIND_FN(onShopBtnClick), defaultBtnSprite, this->dispatcher);
	shop1->setWidth(32);
	shop1->setHeight(32);
	shop1->setPositionX(390);
	shop1->setPositionY(990);
	shop1->registerHoverSprite(hoverBtnSprite);

	auto* shop2 = new Button(12, ColoredText("", Color(255, 255, 255)), BIND_FN(onShopBtnClick), defaultBtnSprite, this->dispatcher);
	shop2->setWidth(32);
	shop2->setHeight(32);
	shop2->setPositionX(340);
	shop2->setPositionY(1030);
	shop2->registerHoverSprite(hoverBtnSprite);

	auto* level1Btn = new Button(1, ColoredText("", Color(255, 255, 255)), BIND_FN(onLevel1BtnClick), defaultBtnSprite, this->dispatcher);
	level1Btn->setWidth(32);
	level1Btn->setHeight(32);
	level1Btn->setPositionX(295);
	level1Btn->setPositionY(363);
	level1Btn->registerHoverSprite(hoverBtnSprite);

	auto* level1TextBtn = new Text(2, new ColoredText("Level 1, Score: " + to_string(savegame->getCurrentGameData().levelData[0].score), Color(0, 0, 0)), 120, 30, 190, 383);

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
	auto* level2TextBtn = new Text(4, new ColoredText(level2Name, Color(0, 0, 0)), 120, 30, 850, 340);

	if (!savegame->getCurrentGameData().levelData[0].completed)
	{
		level2Btn->disable();
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

	auto* level3TextBtn = new Text(6, new ColoredText(level3Name, Color(0, 0, 0)), 120, 30, 690, 870);
	if (!savegame->getCurrentGameData().levelData[1].completed)
	{
		level3Btn->disable();
	}

	auto* stopBtn = new SecondaryButton(7, "To Main Menu", BIND_FN(onStopBtnClick), this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, shop);
	addNewObjectToLayer(3, shopText);
	addNewObjectToLayer(3, shop1);
	addNewObjectToLayer(3, shop2);
	addNewObjectToLayer(3, level1Btn);
	addNewObjectToLayer(3, level1TextBtn);
	addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, level2TextBtn);
	addNewObjectToLayer(3, level3Btn);
	addNewObjectToLayer(3, level3TextBtn);
	addNewObjectToLayer(3, stopBtn);
}

/// @brief 
void Overworld::loadSaveGame()
{
	SpriteObject* emptyBlock = new SpriteObject(-2500, 309, 253, 1, 300, "Assets/Inventory/empty_inventory.png");

	auto* block1 = new Drawable(-2501);
	block1->setStatic(true);
	block1->setPositionX(1200);
	block1->setPositionY(220);
	block1->setWidth(700);
	block1->setHeight(200);
	block1->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block1->changeToState(SpriteState::DEFAULT);


	auto* achievements = new Drawable(-2502);
	achievements->setStatic(true);
	achievements->setPositionX(20);
	achievements->setPositionY(800);
	achievements->setWidth(200);
	achievements->setHeight(500);
	achievements->registerSprite(SpriteState::DEFAULT, emptyBlock);
	achievements->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(4,block1, false, true);
	addNewObjectToLayer(4, achievements, false, true);
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
	engine.loadSound("OVER_WORLD", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
void Overworld::start(bool playSound)
{
	if(playSound)engine.startSound("OVER_WORLD");
}

/// @brief 
void Overworld::onUpdate()
{
}

/// @brief 
void Overworld::onDetach()
{
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

void Overworld::onShopBtnClick()
{
	stateMachine.switchToScene("Shop", false);
}
