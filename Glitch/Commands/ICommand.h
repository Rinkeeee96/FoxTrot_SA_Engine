#pragma once
class ICharacter;
class ICommand
{
public:
	ICommand(ICharacter& _character) : character{ _character } {};
	virtual void execute() const = 0;

protected:
	ICharacter& character;
};