#pragma once
#include "ICommand.h"
class StopMovementCommand : public ICommand
{
public:
	StopMovementCommand(ICharacter& _character) : ICommand(_character) {};
	// Inherited via ICommand
	void execute() const override {
		EventSingleton::get_instance().dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(character.getObjectId()));
	}
};
