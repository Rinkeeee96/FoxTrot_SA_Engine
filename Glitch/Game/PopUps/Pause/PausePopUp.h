#pragma once
#include "Game/PopUps/BasePopup.h"

/// @brief Pause Pop Up
class PausePopUp : public BasePopup
{
public:
	PausePopUp(EventDispatcher& _dispacther, SceneStateMachine& _stateMachine)
		: BasePopup(_dispacther, _stateMachine) {
	};

	void setupPopUp() override;
private:
	void onBackButtonClick();
};