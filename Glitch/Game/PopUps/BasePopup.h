#pragma once
#include "Engine/SceneManager/Layer.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"
#include "Engine\Events\Action\TogglePause.h"

class BasePopup : public Layer
{
public:
	BasePopup(EventDispatcher& _dispatcher, SceneStateMachine& _stateMachine) :
		dispatcher(_dispatcher), stateMachine(_stateMachine) 
	{
	};

	virtual void setupPopUp() = 0;

	void onAttach() override
	{
		TogglePauseEvent pauseEvent(true);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
		setAlwaysVisible(true);

		this->setupPopUp();
	}

	void onDetach() override
	{
		TogglePauseEvent pauseEvent(false);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
		setAlwaysVisible(false);

		this->clearObjects();
	}
protected:
	EventDispatcher& dispatcher;
	SceneStateMachine& stateMachine;
};