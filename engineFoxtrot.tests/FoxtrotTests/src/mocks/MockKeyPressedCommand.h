#pragma once
#include "Engine/Input/Commands/ICommand.h"

class MockKeyPressedCommand : public ICommand {
private:
	std::size_t calls = 0;
public:
	MockKeyPressedCommand() : ICommand("identifier") {}

	virtual void execute(EventDispatcher& dispatcher) { calls++; }
	std::size_t getCalls() const { return calls; }
};