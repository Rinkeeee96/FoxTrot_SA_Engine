#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/Commands/GlobalCommand.h"
#include "Events/Action/IncreaseGameSpeedEvent.h"

class IncreaseGameSpeedCommand : public GlobalCommand
{
public:
	IncreaseGameSpeedCommand(const int _layerId, string identifier) : GlobalCommand(_layerId, identifier) {}
	IncreaseGameSpeedCommand(string identifier) : GlobalCommand(identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		IncreaseGameSpeedEvent increaseSpeed;
		dispatcher.dispatchEvent<IncreaseGameSpeedEvent>(increaseSpeed);
	}
};
