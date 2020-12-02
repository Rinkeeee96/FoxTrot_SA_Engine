#pragma once
#include "Commands/ICharacterCommand.h"
class JumpCommand : public ICharacterCommand
{
public:
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		if (!isEnabled())
			return;

		if (character->getCanJump()) {
			if (character->getXAxisVelocity() > 0)
				character->changeToState(SpriteState::AIR_JUMP_RIGHT);
			else
				character->changeToState(SpriteState::AIR_JUMP_LEFT);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, character->getObjectId()));
		}
	}
};
