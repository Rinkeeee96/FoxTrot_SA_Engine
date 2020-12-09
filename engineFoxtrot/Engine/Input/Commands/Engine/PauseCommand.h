#include "stdafx.h"
#include "Input/Commands/ICommand.h"
#include "General/ISubsystem.h"

#include "Events/Action/TogglePause.h"

class EventDispatcher;

class PauseCommand : public ICommand
{
public:
	PauseCommand(EventDispatcher& dispatcher) : ICommand("pause") {
		// force last pause state to be false to prevent errors 
		// when this command is destroyed and recreated but still paused
		dispatchPauseEvent(dispatcher, false);
	}

	void dispatchPauseEvent(EventDispatcher& dispatcher, bool state) {	
		TogglePauseEvent pauseEvent(state);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);

		lastPauseState = state;
	}

	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override
	{
		bool shouldPause = !lastPauseState;
		dispatchPauseEvent(dispatcher, shouldPause);
	}

private:
	bool lastPauseState;
};
