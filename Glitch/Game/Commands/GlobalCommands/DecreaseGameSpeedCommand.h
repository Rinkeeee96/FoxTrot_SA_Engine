#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/Commands/GlobalCommand.h"
#include "Events/Action/DecreaseGameSpeedEvent.h"

class DecreaseGameSpeedCommand: public GlobalCommand
{
public:
	DecreaseGameSpeedCommand(const int _layerId, string identifier) : GlobalCommand(_layerId, identifier) {}
	DecreaseGameSpeedCommand(string identifier) : GlobalCommand(identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		DecreaseGameSpeedEvent decreaseSpeed;
		dispatcher.dispatchEvent<DecreaseGameSpeedEvent>(decreaseSpeed);
	}
};
