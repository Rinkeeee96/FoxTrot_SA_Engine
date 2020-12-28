#include "pch.h"
#include "Shop.h"
#include "Game/Game.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

/// @brief 
/// Loads all buttons/backgrounds for the shop scene
void Shop::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
	calculateCurrentPrice();

}

/// @brief 
void Shop::onDetach()
{
	Scene::onDetach();
}

/// @brief Starts the scene's sound
/// @param playSound 
void Shop::start(bool playSound)
{
	if (playSound)engine->startSound("MENU_SOUND");
}

/// @brief 
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void Shop::onUpdate(float deltaTime)
{
	if (handlePurchase)
	{
		// Dont check coin count as button should be disabled when under 50 coins
		if (!savegame) return;
		SaveGameData save = savegame->getCurrentGameData();
		save.characterData.totalHealth++;
		save.characterData.inventory.coins -= currentPrice;
		savegame->saveCurrentGameData(save); 
		calculateCurrentPrice();
	}

	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}
}

/// @brief Loads the screen backGground
void Shop::loadBackground()
{
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-1500, 1080, 1920, 1, 0, "Assets/Shop/Shop.png"));
	shared_ptr<SpriteObject> DialogBox = shared_ptr<SpriteObject>(new SpriteObject(-1502, 170, 455, 1, 0, "Assets/Shop/Dialogbox1.png"));
	shared_ptr<SpriteObject> coin = shared_ptr<SpriteObject>(new SpriteObject(-40003, 887, 885, 1, 1, "Assets/Inventory/coin.png"));

	shared_ptr<Text> level1TextBtn = shared_ptr<Text>(new Text(2, new ColoredText("How can I help you today?", Color(0, 0, 0)), 400, 100, 840, 865));

	shared_ptr<Text> heartText = shared_ptr<Text>(new Text(3, new ColoredText("Need extra help? Get some extra hearts!", Color(0, 0, 0)), 400, 80, 150, 260));
	heartText2 = shared_ptr<Text>(new Text(4, new ColoredText("Will cost only " + to_string(currentPrice) + " coins!", Color(0, 0, 0)), 400, 80, 150, 450));

	shared_ptr<SpriteObject> HealthHUD = shared_ptr<SpriteObject>(new SpriteObject(-660, 50, 50, 1, 300, "Assets/Sprites/HUD/Full.png"));
	shared_ptr<Drawable> health = shared_ptr<Drawable>(new Drawable(-700));
	health->setStatic(true);
	health->setPositionX(400);
	health->setPositionY(350);
	health->setWidth(50);
	health->setHeight(50);
	health->setDrawStatic(true);
	health->registerSprite(SpriteState::DEFAULT, HealthHUD);
	health->changeToState(SpriteState::DEFAULT);


	shared_ptr<Drawable> healthBox = shared_ptr<Drawable>(new Drawable(-991));
	healthBox->setStatic(true);
	healthBox->setPositionX(300);
	healthBox->setPositionY(700);
	healthBox->setWidth(500);
	healthBox->setHeight(500);
	healthBox->registerSprite(SpriteState::DEFAULT, DialogBox);
	healthBox->changeToState(SpriteState::DEFAULT);

	text = shared_ptr<Text>(new Text(-39001, new ColoredText(to_string(savegame->getCurrentGameData().characterData.inventory.coins), Color(0, 0, 0), false), 30, 50, 850, 900));
	text->setDrawStatic(true);

	shared_ptr<Drawable> coinObj = shared_ptr<Drawable>(new Drawable(-39000));
	coinObj->setHeight(50);
	coinObj->setWidth(50);
	coinObj->setDrawStatic(true);
	coinObj->setPositionX(910);
	coinObj->setPositionY(900);
	coinObj->registerSprite(SpriteState::DEFAULT, coin);
	coinObj->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> layer0 = shared_ptr<Drawable>(new Drawable(-992));
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> dialogBox = shared_ptr<Drawable>(new Drawable(-994));
	dialogBox->setStatic(true);
	dialogBox->setPositionX(800);
	dialogBox->setPositionY(950);
	dialogBox->setWidth(700);
	dialogBox->setHeight(150);
	dialogBox->registerSprite(SpriteState::DEFAULT, DialogBox);
	dialogBox->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, level1TextBtn, false, true);
	addNewObjectToLayer(1, dialogBox, false, true);

	addNewObjectToLayer(2, text, false, true);
	addNewObjectToLayer(2, coinObj, false, true);
	addNewObjectToLayer(2, health, false, true);
	addNewObjectToLayer(2, healthBox, false, true);
	addNewObjectToLayer(2, heartText, false, true);
	addNewObjectToLayer(2, heartText2, false, true);

}

/// @brief Loads the music for this scene
void Shop::loadMusic()
{
	engine->loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief Loads the buttons for this scene
void Shop::loadButtons()
{
	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(-993, "Overworld", onStopBtnClick, this->dispatcher));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	buyBTN = shared_ptr<PrimaryButton>(new PrimaryButton(-970, "Test", onShopBuyClick, this->dispatcher));

	buyBTN->setPositionX(480);
	buyBTN->setPositionY(350);
	buyBTN->disable();

	addNewObjectToLayer(3, stopBtn);
	addNewObjectToLayer(3, buyBTN);
}


/// @brief Calculate the current price for a new health item in the shop
void Shop::calculateCurrentPrice() {
	int price = HEALTH_PRICE;
	for (int i = 0; i < savegame->getCurrentGameData().characterData.totalHealth-1; i++) {
		price *= INFLATION;
	}
	currentPrice = price;
	updateTextBoxes();
}

/// @brief 
/// A function change all changable textboxes after a update off the currentPrice
void Shop::updateTextBoxes() {
	string name = "Buy!";
	bool lock = false;
	if (savegame->getCurrentGameData().characterData.inventory.coins < currentPrice)
	{
		name = "Not enough coins";
		lock = true;
	}
	if (savegame->getCurrentGameData().characterData.totalHealth >= 10)
	{
		name = "Max amount of health!";
		lock = true;
	}
	buyBTN->changeText(name);

	if (lock) { 
		buyBTN->disable(); 
	}
	else { 
		buyBTN->enable(); 
	}

	string cost = "Will cost only " + to_string(currentPrice) + " coins!";
	heartText2->changeText(cost);

	string coins = to_string(savegame->getCurrentGameData().characterData.inventory.coins);
	text->changeText(coins);
}