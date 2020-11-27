#pragma once
#include "ICharacterCommand.h"
class StopMovementCommand : public ICharacterCommand
{
public:
	StopMovementCommand(ICharacter& _character) : ICharacterCommand(_character) {};
	// Inherited via ICommand
	void execute() const override {
		EventSingleton::get_instance().dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(character.getObjectId()));
	}	
};
