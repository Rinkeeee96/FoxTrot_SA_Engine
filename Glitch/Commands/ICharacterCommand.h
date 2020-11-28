#pragma once
#include "Commands/ICommand.h"
#include "Game/SpriteState.h"
#include "Game/Characters/ICharacter.h"
class Player;
class ICharacterCommand : public ICommand
{
public:
	ICharacterCommand(ICharacter& _character) : character{ _character } {};
	virtual void execute() const override = 0;

protected:
	ICharacter& character;
};