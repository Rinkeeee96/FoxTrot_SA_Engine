#pragma once
#include "Commands/ICharacterCommand.h"

class MoveRightCommand : public ICharacterCommand
{
public:
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {

		if (! isEnabled())
			return;
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, character->getObjectId()));
		if (character->getCanJump()) {
			character->changeToState(SpriteState::RUN_RIGHT);
		}
		else if (character->getYAxisVelocity() > 0)
			character->changeToState(SpriteState::AIR_FALL_RIGHT);
		else
			character->changeToState(SpriteState::AIR_JUMP_RIGHT);
	}
};