#pragma once
#include "ICharacterCommand.h"

class MoveRightCommand : public ICharacterCommand
{
public:
	MoveRightCommand(ICharacter& _character) : ICharacterCommand(_character) {};
	// Inherited via ICommand
	void execute() const override
	{
		EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, character.getObjectId()));
		if (character.getCanJump()) {
			character.changeToState(SpriteState::RUN_RIGHT);
		}
		else if (character.getYAxisVelocity() > 0)
			character.changeToState(SpriteState::AIR_FALL_RIGHT);
		else
			character.changeToState(SpriteState::AIR_JUMP_RIGHT);
	}
};