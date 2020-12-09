#include "stdafx.h"
#include "Input/Commands/ICommand.h"
#include "General/ISubsystem.h"

class PauseCommand : public ICommand
{
public:
	PauseCommand(const vector<ISubsystem*> systems) : systemsToPause{systems}, ICommand("pause") {}
private:
	const vector<ISubsystem*> systemsToPause;

	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override
	{
		for_each(systemsToPause.begin(), systemsToPause.end(), [](ISubsystem* system) {
			system->pause();
		});
	}
};
