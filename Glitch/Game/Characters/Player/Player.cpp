#include "pch.h"
#include "Player.h"

Player::Player(EventDispatcher& _dispatcher) : ICharacter(_dispatcher) {
	this->stateMachine.setCurrentState(new NormalState, this);
	this->stateMachine.setGlobalState(new PlayerGlobalState);
};
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

	this->stateMachine.setCurrentState(new NormalState, this);
	this->stateMachine.setGlobalState(new PlayerGlobalState);

	dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Player::onCollisionBeginEvent));
	dispatcher.setEventCallback<OnCollisionEndEvent>(BIND_EVENT_FN(Player::onCollisionEndEvent));

	dispatcher.setEventCallback<KeyPressedEvent>([this](const Event& event) -> bool {
		releasedKeyLastFrame = false;
		return false;
	});

	dispatcher.setEventCallback<KeyReleasedEvent>([this](const Event& event) -> bool {
		releasedKeyLastFrame = true;
		return false;
	});

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

/// @brief Set the x Velocity of a player. Also changes the sprite state
/// @param val 
void Player::setXAxisVelocity(const float val) {

	if (val == 0 && this->getYAxisVelocity() == 0 && !changed) {
		this->changeToState(SpriteState::DEFAULT);
	}

	Object::setXAxisVelocity(val);
}

/// @brief Set the y Velocity of a player. Also changes the sprite state
/// @param val 
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
/// Handles registration of a custom gamekeypressinvoker
void Player::registerKeypressInvoker(GameKeypressInvoker *_invoker)
{
	invoker = _invoker;
}

/// @brief Clone the player to a new Player
/// @param id 
/// @return 
ICharacter* Player::clone(int id) { 
	return new Player(id, this->dispatcher); 
}

/// @brief
/// Builds the spritemap for the Player
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