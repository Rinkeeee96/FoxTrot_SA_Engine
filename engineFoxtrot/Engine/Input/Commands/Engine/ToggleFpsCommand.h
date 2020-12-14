#include "stdafx.h"
#include "Input/Commands/ICommand.h"
#include "Engine.h"

class EventDispatcher;
class ToggleFpsCommand : public ICommand
{
public:
	ToggleFpsCommand(Engine& _engine): engine{ _engine }, ICommand("toggleFps") {}

	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override
	{
		engine.toggleFps();
	}
private:
	Engine& engine;
	bool lastPauseState = false;
};
