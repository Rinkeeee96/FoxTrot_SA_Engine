#pragma once
#include "Game/Commands/ICharacterCommand.h"
class MoveLeftCommand : public ICharacterCommand
{
public:
	MoveLeftCommand(ICharacter& _character, string identifier) :ICharacterCommand(_character, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::LEFT, character.getObjectId()));
		if (character.getCanJump())
			character.changeToState(SpriteState::RUN_LEFT);
		else if (character.getYAxisVelocity() > 0)
			character.changeToState(SpriteState::AIR_FALL_LEFT);
		else
			character.changeToState(SpriteState::AIR_JUMP_LEFT);
	}
};
