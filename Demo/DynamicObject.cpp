#include "pch.h"
#include "DynamicObject.h"

bool DynamicObject::onKeyPressed(const Event& event) {
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_A:
		this->changeToState(SpriteState::RUN_LEFT);
		this->state = SpriteState::RUN_LEFT;
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::LEFT, this->getObjectId()));
		break;
	case KeyCode::KEY_D:
		this->changeToState(SpriteState::RUN_RIGHT);
		this->state = SpriteState::RUN_RIGHT;
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, this->getObjectId()));
		break;
	case KeyCode::KEY_SPACE:
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
		break;
	default:
		return false;
	}
	return false;
}

bool DynamicObject::onKeyReleased(const Event& event)
{
		auto keyReleasedEvent = static_cast<const KeyReleasedEvent&>(event);

		switch (keyReleasedEvent.GetKeyCode()) {
		case KeyCode::KEY_A:
		case KeyCode::KEY_D:
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->objectId));
			
			changeToState(state == SpriteState::RUN_RIGHT ? SpriteState::IDLE_RIGHT : SpriteState::IDLE_LEFT);
		}
		return false;
}
