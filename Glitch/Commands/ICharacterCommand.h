#pragma once
#include "Input/ICommand.h"

class ICharacter;
class ICharacterCommand : public ICommand
{
public:
	virtual void execute(EventDispatcher& dispatcher) override = 0;

	void registerCharacter(ICharacter* _character) {
		character = _character;
	}

	bool isEnabled() override {
		return character == nullptr;
	}

protected:
	ICharacter* character;
};