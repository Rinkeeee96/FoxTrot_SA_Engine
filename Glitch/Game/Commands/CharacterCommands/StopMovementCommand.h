#pragma once
#include "Game/Commands/ICharacterCommand.h"
class StopMovementCommand : public ICharacterCommand
{
public:
	StopMovementCommand(ICharacter& _character, string identifier) :ICharacterCommand(_character, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(character.getObjectId(), false, true));
	}	
};
