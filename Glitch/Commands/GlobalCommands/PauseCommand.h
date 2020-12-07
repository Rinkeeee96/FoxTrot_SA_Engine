#pragma once
#include "Input/Commands/ICommand.h"
#include <string>
class PauseCommand : public ICommand
{
public:
	PauseCommand(string identifier) : ICommand(identifier) {};
	// Inherited via ICommand
	virtual void execute(EventDispatcher& dispatcher) override {
		cout << "heloooooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
	}
};