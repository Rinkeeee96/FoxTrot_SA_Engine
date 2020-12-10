#pragma once
#include "Game/PopUps/BasePopup.h"

/// @brief Inventory popup class
class InventoryPopup : public BasePopup
{
public:
	InventoryPopup(EventDispatcher& _dispatcher, SceneStateMachine& _stateMachine)
		: BasePopup(_dispatcher, _stateMachine) {};

	void setupPopUp();
};

