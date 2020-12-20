#pragma once
#include "Game/PopUps/Ipopup.h"

/// @brief Pause Pop Up
class PausePopUp : public IPopup
{
public:
	PausePopUp(EventDispatcher& _dispacther, shared_ptr<SceneStateMachine> _stateMachine)
		: IPopup(_dispacther, _stateMachine) {
	};
	// Inherited via BasePopup
	void setupPopUp() override;
private:
	void onBackButtonClick();

	// Inherited via IPopup
	virtual void cleanPopUp() override;
	virtual void onAttach() override;
	virtual void onDetach() override;
};