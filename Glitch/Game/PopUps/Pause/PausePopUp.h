#pragma once
#include "Game/Scenes/Statemachine/SceneStateMachine.h"


/// @brief Pause Pop Up
class PausePopUp : public Layer
{
public:
	PausePopUp(EventDispatcher &_dispacther, SceneStateMachine& _stateMachine);
	~PausePopUp();

	void setupPopUp();

private:
	EventDispatcher &dispatcher;
	SceneStateMachine &stateMachine;

	void onBackButtonClick();
};


