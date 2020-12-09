#pragma once
#include "Game/Scenes/Statemachine/SceneStateMachine.h"



/// @brief Inventory popup class
class InventoryPopup : public Layer
{
public:
	InventoryPopup(EventDispatcher& _dispacther, SceneStateMachine& _stateMachine);
	~InventoryPopup();

	void setupPopUp();

private:
	EventDispatcher& dispatcher;
	SceneStateMachine& stateMachine;

};

