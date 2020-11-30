#pragma once

#include "InputFacade.h"
#include "Events/Action/ActionEvent.h"
#include "Events/Action/FpsToggleEvent.h"
#include "Events/EventSingleton.h"

class Engine;

/// @brief 
/// Input engine for handling input
class InputEngine
{
public:
	API InputEngine(Engine& engine, shared_ptr<EventDispatcher> _dispatcher);
	API ~InputEngine();

	void pollEvents();
private:

	Engine& engine;
	shared_ptr<EventDispatcher> dispatcher;
	IInputFacade *inputFacade;

	bool onKeyPressed(const Event& event);
};
