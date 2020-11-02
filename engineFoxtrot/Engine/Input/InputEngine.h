#pragma once

#include "InputFacade.h"
#include "Events/Action/ActionEvent.h"
#include "Events/Action/FpsToggleEvent.h" //TODO check this
#include "Events/EventSingleton.h"

/// @brief 
/// Input engine for handling input
class DLLEXPORT InputEngine
{
public:
	InputEngine();
	~InputEngine();

	void pollEvents();
private:
	IInputFacade *inputFacade = new InputFacade();

	void onKeyPressed(Event& event);
};
