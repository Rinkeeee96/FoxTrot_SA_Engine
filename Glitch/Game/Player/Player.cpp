#include "Player.h"

Player::Player(int _id): Drawable(_id) {
	this->setHeight(80);
	this->setWidth(80);
	this->setPositionX(100);
	this->setPositionY(80);

	this->setSpeed(75);
	this->setJumpHeight(400);
	this->setDensity(100);
	this->setFriction(0);
	this->setRestitution(0);
	this->setStatic(false);
	this->setRotatable(false);

	// TODO Place collision related event registration in Collidable base class and register virtual methods 
	EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Player::onCollisionBeginEvent));
	EventSingleton::get_instance().setEventCallback<OnCollisionEndEvent>(BIND_EVENT_FN(Player::onCollisionEndEvent));
	EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Player::onKeyPressed));
}

/// @brief 
/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object, 
/// set can jump true
bool Player::onCollisionBeginEvent(Event& event) {
	auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
	if (collisionEvent.GetObjectOneId() != this->getObjectId() && collisionEvent.GetObjectTwoId() != this->getObjectId()) return false;

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
	// TODO when should onCollisionBeginEvent be handled, default is false so it continues without breaking current functionality
	return false;
}

/// @brief 
/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
bool Player::onCollisionEndEvent(Event& event) {
	// TODO when should this event be "handled"? should each collision be handled or should it end as soon as an entity is found?
	auto collisionEvent = static_cast<OnCollisionEndEvent&>(event);
	if (collisionEvent.GetObjectOneId() != this->getObjectId() && collisionEvent.GetObjectTwoId() != this->getObjectId()) return false;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::DOWN) != collidedDirection.end()) {
		this->canJump = false;
	}
	// TODO when should onCollisionEndEvent be handled, default is false so it continues without breaking current functionality
	return false;
}

void Player::setYAxisVelocity(const float val) {

	if (!canJump) {
		// TODO do we need this after refactor?
		if (val > 0 && !changed) {
			if (this->getXAxisVelocity() > 0)
				this->changeToState(SpriteState::AIR_FALL_RIGHT);
			else
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
bool Player::onKeyPressed(Event& event) {
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
			return true;
	case KeyCode::KEY_D:
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, this->getObjectId()));
			if (canJump) {
				this->changeToState(SpriteState::RUN_RIGHT);
			}
			else if (this->getYAxisVelocity() > 0)
				this->changeToState(SpriteState::AIR_FALL_RIGHT);
			else 
				this->changeToState(SpriteState::AIR_JUMP_RIGHT);
			return true;
	case KeyCode::KEY_SPACE:
		if (canJump) {
			if (this->getXAxisVelocity() > 0)
				this->changeToState(SpriteState::AIR_JUMP_RIGHT);
			else
				this->changeToState(SpriteState::AIR_JUMP_LEFT);
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
		}
		return true;
	default:
		return false;
	}
}

bool Player::getCanJump() const { return this->canJump; };
void Player::setCanJump(bool val) { this->canJump = val; }