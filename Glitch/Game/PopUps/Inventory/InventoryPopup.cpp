#include "pch.h"
#include "InventoryPopup.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/SpriteState.h"

#define BIND_FN(function) std::bind(&InventoryPopup::function, *this)

InventoryPopup::InventoryPopup(EventDispatcher& _dispatcher, SceneStateMachine& _stateMachine) :
	dispatcher(_dispatcher), stateMachine(_stateMachine)
{
}

InventoryPopup::~InventoryPopup()
{
}

/// @brief Setup the Pause Pop Up.
void InventoryPopup::setupPopUp()
{
	SpriteObject* rightInven = new SpriteObject(-564577, 343, 614, 1, 1, "Assets/Inventory/Right.png");
	SpriteObject* leftInven = new SpriteObject(-564578, 402, 255, 1, 1, "Assets/Inventory/Left.png");

	Drawable* leftInventory = new Drawable(-564579);
	leftInventory->setHeight(600);
	leftInventory->setWidth(400);
	leftInventory->setPositionX(WINDOW_WIDTH_CENTER - 600);
	leftInventory->setPositionY(WINDOW_HEIGHT_CENTER + 200);
	leftInventory->setDrawStatic(true);
	leftInventory->registerSprite(SpriteState::DEFAULT, leftInven);
	leftInventory->changeToState(SpriteState::DEFAULT);

	Drawable* rightInventory = new Drawable(-564574);
	rightInventory->setHeight(400);
	rightInventory->setWidth(600);
	rightInventory->setDrawStatic(true);
	rightInventory->setPositionX(WINDOW_WIDTH_CENTER);
	rightInventory->setPositionY(WINDOW_HEIGHT_CENTER + 200);
	rightInventory->registerSprite(SpriteState::DEFAULT, rightInven);
	rightInventory->changeToState(SpriteState::DEFAULT);

	addObjectInLayer(leftInventory);
	addObjectInLayer(rightInventory);

}
