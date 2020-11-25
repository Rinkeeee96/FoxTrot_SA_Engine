#include "pch.h"
#include "Player.h"

Player::Player(const int id) : ICharacter(id) {
	this->setHeight(80);
	this->setWidth(80);
	this->setPositionX(100);
	this->setPositionY(80);

	this->setSpeed(6);
	this->setJumpHeight(10);
	this->setDensity(200);
	this->setFriction(0);
	this->setRestitution(0);
	this->setStatic(false);
	this->setRotatable(false);

	this->setHealth(3);
	this->setScalable(true);
	this->setScale(2);

	EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Player::onCollisionBeginEvent));
	EventSingleton::get_instance().setEventCallback<OnCollisionEndEvent>(BIND_EVENT_FN(Player::onCollisionEndEvent));
	EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Player::onKeyPressed));
}

/// @brief 
/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object, 
/// set can jump true
bool Player::onCollisionBeginEvent(Event& event) {
	if (!getIsDead()) {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

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
	return false;
}

/// @brief 
/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
bool Player::onCollisionEndEvent(Event& event) {
	if (!getIsDead()) {
		auto collisionEvent = static_cast<OnCollisionEndEvent&>(event);
		if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getObjectId()];

		if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::DOWN) != collidedDirection.end()) {
			this->canJump = false;
		}
	}

	return false;
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
bool Player::onKeyPressed(Event& event) {
	ICommand* command = nullptr;
	CommandInvoker movementInvoker;
	movementInvoker.SetOnFinish(new StopMovementCommand(*this));

	bool handled = true;

	if (!getIsDead()) {
		auto keyPressedEvent = static_cast<KeyPressedEvent&>(event);
		// TODO command pattern
		switch (keyPressedEvent.GetKeyCode())
		{
		case KeyCode::KEY_A: 
			movementInvoker.SetOnStart(new MoveLeftCommand(*this), []() -> bool {
				bool released = false;
				EventSingleton::get_instance().setEventCallback<KeyReleasedEvent>([&released](Event& e) -> bool {
					released = static_cast<KeyReleasedEvent&>(e).GetKeyCode() == KeyCode::KEY_A;
					return true;
				});
				return released;
			});
			break;
		case KeyCode::KEY_D: 
			movementInvoker.SetOnStart(new MoveRightCommand(*this), []() -> bool {
				bool released = false;
				EventSingleton::get_instance().setEventCallback<KeyReleasedEvent>([&released](Event& e) -> bool {
					released = static_cast<KeyReleasedEvent&>(e).GetKeyCode() == KeyCode::KEY_D;
					return true;
				});
				return released;
			});
			break;
		case KeyCode::KEY_SPACE: 
			command = new JumpCommand(*this);
			command->execute();
			break;
		default:
			handled = false;
		}

		movementInvoker.execute();
		if (command) {
			delete command;
		}

	}
	return handled;
}

ICharacter* Player::clone(int id) { return new Player(id); }