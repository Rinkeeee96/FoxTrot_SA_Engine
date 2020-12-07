#include "pch.h"
#include "Player.h"

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
	dispatcher.setEventCallback<KeyReleasedEvent>(BIND_EVENT_FN(Player::onKeyReleased));
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
		this->canJump = true;
	}

	Object::setYAxisVelocity(val);
}

/// @brief 
/// Handles when an key pressed event happend, Player can move right, left and jump
bool Player::onKeyPressed(const Event& event) {
	if (!getIsDead()) {
		auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
		// TODO command pattern
		switch (keyPressedEvent.GetKeyCode())
		{
		case KeyCode::KEY_A:
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::LEFT, this->getObjectId()));
			if (canJump)
				this->changeToState(SpriteState::RUN_LEFT);
			else if (this->getYAxisVelocity() > 0)
				this->changeToState(SpriteState::AIR_FALL_LEFT);
			else
				this->changeToState(SpriteState::AIR_JUMP_LEFT);
			break;
		case KeyCode::KEY_D:
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, this->getObjectId()));
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
				dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			}
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
}

bool Player::onKeyReleased(const Event& event)
{
	if (!getIsDead()) {
		auto keyReleasedEvent = static_cast<const KeyReleasedEvent&>(event);

		switch (keyReleasedEvent.GetKeyCode()) {
		case KeyCode::KEY_A:
		case KeyCode::KEY_D:
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->objectId));
		}

		return false;
	}
	return false;
}

ICharacter* Player::clone(int id) { 
	return new Player(id, this->dispatcher); 
}

map<SpriteState, SpriteObject*> Player::buildSpritemap(int textureId) {
	std::map<SpriteState, SpriteObject*> spriteMap;

	auto playerDefault = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Character/adventure.png");
	auto playerAirAttack = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png");
	auto playerRunRight = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 6, 200, "Assets/Sprites/Character/adventure_run_right.png");
	auto playerSlide = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_slide.png");
	auto playerFallLeft = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png");
	auto playerFallRight = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");
	auto playerJumpLeft = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png");
	auto playerRunLeft = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 6, 200, "Assets/Sprites/Character/adventure_run_left.png");
	auto playerJumpRight = new SpriteObject(textureId++, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png");

	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, playerDefault));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_ATTACK, playerAirAttack));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::RUN_RIGHT, playerRunRight));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::SLIDE, playerSlide));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_FALL_LEFT, playerFallLeft));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_JUMP_LEFT, playerJumpLeft));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_FALL_RIGHT, playerFallRight));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_JUMP_RIGHT, playerJumpRight));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::RUN_LEFT, playerRunLeft));

	return spriteMap;
}