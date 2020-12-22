#include "pch.h"
#include "SlimeBoss.h"
#include <Game/Levels/Level.h>

SlimeBoss::SlimeBoss(Level& _level, EventDispatcher& _dispatcher) : IEnemy(_dispatcher), level(_level) {
	this->stateMachine.setCurrentState(make_unique<SlimeBossNormalState>(), *this);
	this->stateMachine.setGlobalState(make_unique<SlimeBossGlobalState>(), *this);
}
SlimeBoss::SlimeBoss(Level& _level, const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher), level(_level) { 
	_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(SlimeBoss::onCollisionBeginEvent));
	this->stateMachine.setCurrentState(make_unique<SlimeBossNormalState>(), *this);
	this->stateMachine.setGlobalState(make_unique<SlimeBossGlobalState>(), *this);
}

bool SlimeBoss::onCollisionBeginEvent(const Event& event) {
	auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
	if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
		if (collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				if (!this->invincible) this->currentHealth--;
			}
		}
		else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				if(!this->invincible) this->currentHealth--;
			}
		}
	}
	else {
		if (collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				this->doDamage();
			}
		}
		else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				this->doDamage();
			}
		}
	}
	return false;
}

/// @brief
/// Checks if the player is within range and acts accordingly
/// The Slime will jump if it is on the ground
/// If the player is below the Slime, it will add a downwards velocity to reach the player faster
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void SlimeBoss::onUpdate(float deltaTime) {
	if (this->getIsDead()) {
		this->level.setWin(true);
		return;
	}
	bool positionedOnGround = this->getYAxisVelocity() == 0;
	float slimeMiddleXPosition = this->getPositionX() + (this->getWidth() / 2);
	bool playerIsLowerThanMe = this->getPositionY() < player->getPositionY();
	bool playerIsWithinXLevelRange = (slimeMiddleXPosition >= player->getPositionX()) && (slimeMiddleXPosition <= (player->getPositionX() + player->getWidth()));

	if (positionedOnGround && !jumping) {
		jumping = true;
	}

	if (playerIsLowerThanMe && playerIsWithinXLevelRange) {
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::DOWN, this->getObjectId()));
	}

	if (jumping) {
		jumpTimer += deltaTime;
		if (jumpTimer < (SLIME_JUMP_ANIMATION_TIME / 2)) {
			changeToState(SpriteState::ACTION_2);
		}
		else if (jumpTimer >= (SLIME_JUMP_ANIMATION_TIME / 2) && jumpTimer < SLIME_JUMP_ANIMATION_TIME) {
			changeToState(SpriteState::ACTION_1);
		}
		else if (jumpTimer >= SLIME_JUMP_ANIMATION_TIME) {
			changeToState(SpriteState::ACTION_3);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			jumpTimer = 0;
			jumping = false;
		}
	}
	stateMachine.update(*this);
}

/// @brief
/// Builds the spritemap for the Slime
map<SpriteState, shared_ptr<SpriteObject>> SlimeBoss::buildSpritemap(int textureId) {
	std::map<SpriteState, shared_ptr<SpriteObject>> spriteMap;

	auto slimeDefault = shared_ptr<SpriteObject>(new SpriteObject(textureId++, SLIME_IDLE_SPRITE_HEIGHT, SLIME_IDLE_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_default.png"));
	auto slimeAction1 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, SLIME_ACTION_SPRITE_HEIGHT, SLIME_ACTION_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action_1.png"));
	auto slimeAction2 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, SLIME_ACTION_SPRITE_HEIGHT, SLIME_ACTION_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action_2.png"));
	auto slimeAction3 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, SLIME_ACTION_SPRITE_HEIGHT, SLIME_ACTION_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action_3.png"));

	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::DEFAULT, slimeDefault));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_1, slimeAction1));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_2, slimeAction2));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_3, slimeAction3));

	return spriteMap;
}