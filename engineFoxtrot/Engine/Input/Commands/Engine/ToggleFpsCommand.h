#include "stdafx.h"
#include "Input/Commands/ICommand.h"
#include "video/VideoEngine.h"

class EventDispatcher;
class ToggleFpsCommand : public ICommand
{
public:
	ToggleFpsCommand(VideoEngine& _engine): engine{ _engine }, ICommand("toggleFps") {}

	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override
	{
		engine.toggleFps();
	}
private:
	VideoEngine& engine;
	bool lastPauseState = false;
};
