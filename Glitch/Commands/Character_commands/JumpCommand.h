#pragma once
#include "Commands/ICharacterCommand.h"
class JumpCommand : public ICharacterCommand
{
public:
	JumpCommand(ICharacter& _character) : ICharacterCommand(_character) {};
	// Inherited via ICommand
	void execute() const override {
		if (character.getCanJump()) {
			if (character.getXAxisVelocity() > 0)
				character.changeToState(SpriteState::AIR_JUMP_RIGHT);
			else
				character.changeToState(SpriteState::AIR_JUMP_LEFT);
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, character.getObjectId()));
		}
	}
};
