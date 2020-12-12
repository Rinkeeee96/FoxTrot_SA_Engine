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
	virtual void cleanPopUp() {
		for (pair<const int, Object*> obj : objects)
			delete obj.second;

		this->clearObjects();
	};

	virtual void onAttach() override
	{
		TogglePauseEvent pauseEvent(true);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
		setAlwaysVisible(true);

		this->setupPopUp();
	}

	virtual void onDetach() override
	{
		TogglePauseEvent pauseEvent(false);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
		setAlwaysVisible(false);

		this->cleanPopUp();
	}
protected:
	EventDispatcher& dispatcher;
	SceneStateMachine& stateMachine;
};