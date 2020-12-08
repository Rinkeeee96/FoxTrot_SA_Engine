#pragma once
#include "Game/Commands/ICharacterCommand.h"
class JumpCommand : public ICharacterCommand
{
public:
	JumpCommand(ICharacter& _character, string identifier) : ICharacterCommand(_character, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		if (character.getCanJump()) {
			if (character.getXAxisVelocity() > 0)
				character.changeToState(SpriteState::AIR_JUMP_RIGHT);
			else
				character.changeToState(SpriteState::AIR_JUMP_LEFT);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, character.getObjectId()));
		}
	}
};
