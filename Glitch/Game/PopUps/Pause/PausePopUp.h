#pragma once
#include "Game/PopUps/BasePopup.h"

/// @brief Pause Pop Up
class PausePopUp : public BasePopup
{
public:
	PausePopUp(EventDispatcher& _dispacther, shared_ptr<SceneStateMachine> _stateMachine)
		: BasePopup(_dispacther, _stateMachine) {
	};
	// Inherited via BasePopup
	void setupPopUp() override;
private:
	void onBackButtonClick();
};