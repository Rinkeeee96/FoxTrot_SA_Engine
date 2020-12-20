#pragma once
#include "Game/PopUps/Ipopup.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"

/// @brief Inventory popup class
class InventoryPopup : public IPopup
{
public:
	InventoryPopup(EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine)
		: IPopup(_dispatcher, _stateMachine) {};

	void setupPopUp() override;
	virtual void cleanPopUp() override;
	virtual void onAttach() override;
	virtual void onDetach() override;
};

