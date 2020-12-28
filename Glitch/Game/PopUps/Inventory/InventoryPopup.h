#pragma once
#include "Game/PopUps/PauseablePopup.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"

/// @brief Inventory popup class
class InventoryPopup : public PauseablePopup
{
public:
	InventoryPopup(unique_ptr<Engine>& _engine, EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine)
		: PauseablePopup(_engine, _dispatcher, _stateMachine) {};

	void setupPopUp() override;
	virtual void cleanPopUp() override;
	virtual void onAttach() override;
	virtual void onDetach() override;
	void onUpdate() override {};

	void changeCoinCount(const int coin);

private:
	shared_ptr<Text> text;
};

