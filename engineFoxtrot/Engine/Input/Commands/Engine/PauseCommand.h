#include "Input/Commands/ICommand.h"
#include "General/ISubsystem.h"

class PauseCommand : public ICommand
{
public:
	PauseCommand(const vector<const ISubsystem*> systems) : systemsToPause{systems}, ICommand("pause") {}
private:
	const vector<const ISubsystem*> systemsToPause;

	// Inherited via ICommand
	virtual void execute(EventDispatcher& dispatcher) override;
};

void PauseCommand::execute(EventDispatcher& dispatcher)
{
	for_each(systemsToPause.begin(), systemsToPause.end(), [](ISubsystem& system) {
		system.pause();
	});
}
