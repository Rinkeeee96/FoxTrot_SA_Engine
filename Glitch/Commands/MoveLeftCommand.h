#pragma once
#include "ICommand.h"
class MoveLeftCommand : public ICommand
{
public:
	MoveLeftCommand(ICharacter& _character) : ICommand(_character) {};
	// Inherited via ICommand
	void execute() const override {
		if (character.getCanJump())
			character.changeToState(SpriteState::RUN_LEFT);
		else if (character.getYAxisVelocity() > 0)
			character.changeToState(SpriteState::AIR_FALL_LEFT);
		else
			character.changeToState(SpriteState::AIR_JUMP_LEFT);
	}
};
