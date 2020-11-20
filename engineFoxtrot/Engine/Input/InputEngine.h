#pragma once

#include "InputFacade.h"
#include "Events/Action/ActionEvent.h"
#include "Events/Action/FpsToggleEvent.h"
#include "Events/EventSingleton.h"

/// @brief 
/// Input engine for handling input
class InputEngine
{
public:
	API InputEngine();
	API ~InputEngine();

	void pollEvents();
private:
	IInputFacade *inputFacade = new InputFacade();

	bool onKeyPressed(Event& event);
};
