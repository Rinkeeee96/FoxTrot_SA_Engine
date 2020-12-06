#pragma once
#include "Input/Commands/ICommand.h"

class ICharacter;
class ICharacterCommand : public ICommand
{
public:
	ICharacterCommand(ICharacter& _character, string identifier) : character{_character}, ICommand(identifier) {}
	virtual void execute(EventDispatcher& dispatcher) override = 0;
protected:
	ICharacter& character;
};