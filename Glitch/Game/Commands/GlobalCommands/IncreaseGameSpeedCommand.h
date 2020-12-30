#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/Commands/GlobalCommand.h"
#include "Events/Action/IncreaseGameSpeedEvent.h"

class IncreaseGamesSpeedCommand : public GlobalCommand
{
public:
	IncreaseGamesSpeedCommand(string identifier) : GlobalCommand(identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		IncreaseGameSpeedEvent increaseSpeed;
		dispatcher.dispatchEvent<IncreaseGameSpeedEvent>(increaseSpeed);
	}
};
