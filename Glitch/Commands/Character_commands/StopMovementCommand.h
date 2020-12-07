#pragma once
#include "Commands/ICharacterCommand.h"
class StopMovementCommand : public ICharacterCommand
{
public:
	StopMovementCommand(ICharacter& _character, string identifier) :ICharacterCommand(_character, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		if (character.getCanJump() || character.getYAxisVelocity() == 0)
		{
		dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(character.getObjectId()));

		}
	}	
};
