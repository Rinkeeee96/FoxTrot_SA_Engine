#pragma once
#include "Commands/ICommand.h"

class ICharacter;
class ICharacterCommand : public ICommand
{
public:
	ICharacterCommand(ICharacter& _character) : character{ _character } {};
	virtual void execute() const override = 0;

protected:
	ICharacter& character;
};