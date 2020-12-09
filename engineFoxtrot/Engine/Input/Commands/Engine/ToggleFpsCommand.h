#include "stdafx.h"
#include "Input/Commands/ICommand.h"
#include "video/VideoEngine.h"
class EventDispatcher;
class ToggleFpsCommand : public ICommand
{
public:
	ToggleFpsCommand(VideoEngine& _engine): engine{ _engine }, ICommand("toggleFps") {}

	void dispatchPauseEvent(EventDispatcher& dispatcher, bool state) {
		TogglePauseEvent pauseEvent(state);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);

		lastPauseState = state;
	}

	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override
	{
		engine.toggleFps();
	}

private:
	VideoEngine& engine;
	bool lastPauseState = false;
};
