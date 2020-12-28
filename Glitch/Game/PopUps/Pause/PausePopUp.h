#pragma once
#include "Game/PopUps/PauseablePopup.h"

/// @brief Pause Pop Up
class PausePopUp : public PauseablePopup
{
public:
	PausePopUp(unique_ptr<Engine>& _engine, EventDispatcher& _dispacther, shared_ptr<SceneStateMachine> _stateMachine)
		: PauseablePopup(_engine, _dispacther, _stateMachine) {
	};
	// Inherited via BasePopup
	void setupPopUp() override;
	void onUpdate() override {};
	// Inherited via IPopup
	virtual void cleanPopUp() override;
	virtual void onAttach() override;
	virtual void onDetach() override;
private:
	void onBackButtonClick();

};