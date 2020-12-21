#pragma once
#include "Engine/SceneManager/Layer.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"
#include "Engine\Events\Action\TogglePause.h"
/// @brief Interface class for a popUp
class IPopup : public Layer
{
public:
	IPopup(unique_ptr<Engine>& _engine ,EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine) :
		engine{ _engine },dispatcher(_dispatcher), stateMachine(_stateMachine) {};

	virtual void setupPopUp() = 0;
	virtual void cleanPopUp() = 0;

	virtual void onAttach() override = 0;
	virtual void onDetach() override = 0;

protected:
	unique_ptr<Engine>& engine;
	EventDispatcher& dispatcher;
	shared_ptr<SceneStateMachine> stateMachine;
};