#include "pch.h"
#include "Player.h"
#include <Commands\Character_commands\StopMovementCommand.h>

Player::Player(const int id, EventDispatcher& _dispatcher) : ICharacter(id, _dispatcher) {
	this->setHeight(80);
	this->setWidth(80);
	this->setPositionX(100);
	this->setPositionY(80);

	this->setSpeed(6);
	this->setJumpHeight(10);
	this->setDensity(10);
	this->setFriction(0);
	this->setRestitution(0.1f);
	this->setTotalHealth(3);
	this->setStatic(false);
	this->setRotatable(false);

	this->setCurrentHealth(3);
	this->setTotalHealth(3);
	this->setScalable(true);
	this->setScale(2);

	dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Player::onCollisionBeginEvent));
	dispatcher.setEventCallback<OnCollisionEndEvent>(BIND_EVENT_FN(Player::onCollisionEndEvent));
	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Player::onKeyPressed));
}

/// @brief 
/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object, 
/// set can jump true
bool Player::onCollisionBeginEvent(const Event& event) {
	if (!getIsDead()) {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
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
bool Player::onCollisionEndEvent(const Event& event) {
	if (!getIsDead()) {
		auto collisionEvent = static_cast<const OnCollisionEndEvent&>(event);
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
		if (val > RESTITUTION_CORRECTION && !changed) {
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
bool Player::onKeyPressed(const Event& event) {
	if (!getIsDead()) {
		auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
		keypressInvoker->executeCommand(keyPressedEvent.GetKeyCode());
	}
	return false;
}

void Player::registerKeypressInvoker(GameKeypressInvoker* invoker)
{
	keypressInvoker = invoker;
}

void Player::onUpdate()
{
	// welke toest is pressed?
	// call invoker met pressed key
	// hoe komen we hier aan pressed key?
}

ICharacter* Player::clone(int id) { 
	return new Player(id, this->dispatcher); 
}