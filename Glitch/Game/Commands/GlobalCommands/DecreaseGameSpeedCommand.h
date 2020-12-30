#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/Commands/GlobalCommand.h"
#include "Events/Action/DecreaseGameSpeedEvent.h"

class IncreaseGamesSpeedCommand : public GlobalCommand
{
public:
	IncreaseGamesSpeedCommand(string identifier) : GlobalCommand(identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		DecreaseGameSpeedEvent decreaseSpeed;
		dispatcher.dispatchEvent<DecreaseGameSpeedEvent>(decreaseSpeed);
	}
};
