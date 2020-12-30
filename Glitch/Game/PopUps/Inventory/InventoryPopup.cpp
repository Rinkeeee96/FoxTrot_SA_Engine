#include "pch.h"
#include "InventoryPopup.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/SpriteState.h"

#define BIND_FN(function) std::bind(&InventoryPopup::function, *this)

/// @brief Setup for the popup inventory layer
void InventoryPopup::setupPopUp()
{
	shared_ptr<SpriteObject> rightInven = shared_ptr<SpriteObject>(new SpriteObject(-40000, 343, 614, 1, 1, "Assets/Inventory/right.png"));
	shared_ptr<SpriteObject> leftInven = shared_ptr<SpriteObject>(new SpriteObject(-40002, 402, 255, 1, 1, "Assets/Inventory/left.png"));
	shared_ptr<SpriteObject> coin = shared_ptr<SpriteObject>(new SpriteObject(-40003, 887, 885, 1, 1, "Assets/Inventory/coin.png"));

	text = shared_ptr<Text>(new Text(-39001, new ColoredText("0", Color(0, 0, 0), false),30, 50,450 , 805));
	text->setDrawStatic(true);

	shared_ptr<Drawable> leftInventory = shared_ptr<Drawable>(new Drawable(-40004));
	leftInventory->setHeight(600);
	leftInventory->setWidth(400);
	leftInventory->setPositionX(WINDOW_WIDTH_CENTER - 600);
	leftInventory->setPositionY(WINDOW_HEIGHT_CENTER + 330);
	leftInventory->setDrawStatic(true);
	leftInventory->registerSprite(SpriteState::DEFAULT, leftInven);
	leftInventory->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> rightInventory = shared_ptr<Drawable>(new Drawable(-40006));
	rightInventory->setHeight(600);
	rightInventory->setWidth(600);
	rightInventory->setDrawStatic(true);
	rightInventory->setPositionX(WINDOW_WIDTH_CENTER);
	rightInventory->setPositionY(WINDOW_HEIGHT_CENTER + 330);
	rightInventory->registerSprite(SpriteState::DEFAULT, rightInven);
	rightInventory->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> coinObj = shared_ptr<Drawable>(new Drawable(-39000));
	coinObj->setHeight(50);
	coinObj->setWidth(50);
	coinObj->setDrawStatic(true);
	coinObj->setPositionX(535);
	coinObj->setPositionY(810);
	coinObj->registerSprite(SpriteState::DEFAULT, coin);
	coinObj->changeToState(SpriteState::DEFAULT);

	addObjectInLayer(text);
	addObjectInLayer(coinObj);
	addObjectInLayer(leftInventory);
	addObjectInLayer(rightInventory);
}

void InventoryPopup::cleanPopUp()
{
	this->clearObjects();
}

void InventoryPopup::onAttach()
{
	this->stateMachine->registerActivePopup(this);
	this->setupPopUp();
	setAlwaysVisible(true);

	if (this->stateMachine->activePopupCount() <= 1) {
		TogglePauseEvent pauseEvent(true);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	}
}

void InventoryPopup::onDetach()
{
	this->stateMachine->deregisterActivePopup(this);
	this->cleanPopUp();
	setAlwaysVisible(false);

	if (this->stateMachine->activePopupCount() <= 0) {
		TogglePauseEvent pauseEvent(false);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	}
}



/// @brief 
/// @param coin 
void InventoryPopup::changeCoinCount(const int coin)
{
	string coins = to_string(coin);
	if(text)text->changeText(coins);
}

