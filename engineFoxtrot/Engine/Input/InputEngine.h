#pragma once

#include "InputFacade.h"
#include "Events/Action/ActionEvent.h"
#include "Events/EventSingleton.h"

class Engine;

/// @brief 
/// Input engine for handling input
class InputEngine
{
public:
	API InputEngine(Engine& engine);
	API ~InputEngine();

	void pollEvents();
private:

	Engine& engine;
	IInputFacade *inputFacade = new InputFacade();

	bool onKeyPressed(Event& event);
};
