#pragma once
#include "Game/Commands/ICharacterCommand.h"

class MoveRightCommand : public ICharacterCommand
{
public:
	MoveRightCommand(ICharacter& _character, string identifier) :ICharacterCommand(_character, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, character.getObjectId()));
		if (character.getCanJump()) {
			character.changeToState(SpriteState::RUN_RIGHT);
		}
		else if (character.getYAxisVelocity() > 1) 
			character.changeToState(SpriteState::AIR_FALL_RIGHT);
		else if (character.getYAxisVelocity() < -1)
			character.changeToState(SpriteState::AIR_JUMP_RIGHT);
	}
};