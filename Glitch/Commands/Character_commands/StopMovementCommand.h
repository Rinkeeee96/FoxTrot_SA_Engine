#pragma once
#include "Commands/ICharacterCommand.h"
class StopMovementCommand : public ICharacterCommand
{
public:
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		if (!isEnabled())
			return;
		dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(character->getObjectId()));
	}	
};
