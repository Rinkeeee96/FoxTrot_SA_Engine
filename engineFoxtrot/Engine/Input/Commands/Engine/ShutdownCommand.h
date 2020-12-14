#include "stdafx.h"
#include "Input/Commands/ICommand.h"
#include "Engine.h"

class EventDispatcher;

class ShutdownCommand : public ICommand
{
public:
	ShutdownCommand(Engine& _engine) : engine{ _engine }, ICommand("shutdown") {}

	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override
	{
		engine.shutdown();
	}

private:
	Engine& engine;
};
