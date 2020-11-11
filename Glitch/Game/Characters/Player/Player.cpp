#include "Player.h"

Player::Player(const int id) : ICharacter(id) {
	this->setName("person");
	this->setHeight(80);
	this->setWidth(80);
	this->setPositionX(100);
	this->setPositionY(80);

	this->setSpeed(75);
	this->setJumpHeight(400);
	this->setDensity(200);
	this->setFriction(0);
	this->setRestitution(0);
	this->setStatic(false);
	this->setRotatable(false);

	EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Player::onCollisionBeginEvent));
	EventSingleton::get_instance().setEventCallback<OnCollisionEndEvent>(BIND_EVENT_FN(Player::onCollisionEndEvent));
	EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Player::onKeyPressed));
	EventSingleton::get_instance().setEventCallback<KeyReleasedEvent>(BIND_EVENT_FN(Player::onKeyReleased));
}

/// @brief 
/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object, 
/// set can jump true
void Player::onCollisionBeginEvent(Event& event) {
	auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
	if (collisionEvent.GetObjectOneId() != this->getObjectId() && collisionEvent.GetObjectTwoId() != this->getObjectId()) return;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::DOWN) != collidedDirection.end()) {
		this->canJump = true;
		if (this->getXAxisVelocity() == 0)
			this->changeToState(SpriteState::DEFAULT);
		else if (this->getXAxisVelocity() > 0)
			this->changeToState(SpriteState::RUN_RIGHT);
		else
			this->changeToState(SpriteState::RUN_LEFT);
	}
}

/// @brief 
/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
void Player::onCollisionEndEvent(Event& event) {
	auto collisionEvent = static_cast<OnCollisionEndEvent&>(event);
	if (collisionEvent.GetObjectOneId() != this->getObjectId() && collisionEvent.GetObjectTwoId() != this->getObjectId()) return;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::DOWN) != collidedDirection.end()) {
		this->canJump = false;
	}
}

void Player::setXAxisVelocity(const float val) {

	if (val == 0 && this->getYAxisVelocity() == 0 && !changed) {
		this->changeToState(SpriteState::DEFAULT);
	}

	Object::setXAxisVelocity(val);
}

void Player::setYAxisVelocity(const float val) {

	if (!canJump) {
		if (val > 0 && !changed) {
			if (this->getXAxisVelocity() > 0 || this->currentSpriteState == SpriteState::AIR_JUMP_RIGHT)
				this->changeToState(SpriteState::AIR_FALL_RIGHT);
			else if (this->currentSpriteState != AIR_FALL_RIGHT)
				this->changeToState(SpriteState::AIR_FALL_LEFT);
		}
	}

	if (val == 0) {
		changed = false;
	}

	Object::setYAxisVelocity(val);
}

/// @brief 
/// Handles when an key pressed event happend, Player can move right, left and jump
void Player::onKeyPressed(Event& event) {
	auto keyPressedEvent = static_cast<KeyPressedEvent&>(event);
	// TODO command pattern
	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_A:
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::LEFT, this->getObjectId()));
			if (canJump)
				this->changeToState(SpriteState::RUN_LEFT);
			else if (this->getYAxisVelocity() > 0) 
				this->changeToState(SpriteState::AIR_FALL_LEFT);
			else
				this->changeToState(SpriteState::AIR_JUMP_LEFT);
		break;
	case KeyCode::KEY_D:
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, this->getObjectId()));
			if (canJump) {
				this->changeToState(SpriteState::RUN_RIGHT);
			}
			else if (this->getYAxisVelocity() > 0)
				this->changeToState(SpriteState::AIR_FALL_RIGHT);
			else 
				this->changeToState(SpriteState::AIR_JUMP_RIGHT);
		break;
	case KeyCode::KEY_SPACE:
		if (canJump) {
			if (this->getXAxisVelocity() > 0)
				this->changeToState(SpriteState::AIR_JUMP_RIGHT);
			else
				this->changeToState(SpriteState::AIR_JUMP_LEFT);
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
		}
		break;
	default:
		break;
	}
}

void Player::onKeyReleased(Event& event)
{
	auto keyReleasedEvent = static_cast<KeyReleasedEvent&>(event);
	
	switch (keyReleasedEvent.GetKeyCode()) {
		case KeyCode::KEY_A:
		case KeyCode::KEY_D:
			EventSingleton::get_instance().dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->objectId));
	}
}