#include "pch.h"
#include "SlimeBoss.h"
#include <Game/Levels/Level.h>
#include <Game/Characters/Enemies/Fleye.h>
#include <Game/Characters/Enemies/Slime.h>
/// @brief Constructor setting statemachine
/// @param _level 
/// @param _dispatcher 
SlimeBoss::SlimeBoss(Level& _level, EventDispatcher& _dispatcher) : IEnemy(_dispatcher), level(_level) {
	this->invincible = false;
	this->stateMachine.setCurrentState(make_unique<SlimeBossNormalState>(), *this);
	this->stateMachine.setGlobalState(make_unique<SlimeBossGlobalState>(), *this);
}

/// @brief Constructor setting statemachine
/// @param _level 
/// @param _dispatcher 
SlimeBoss::SlimeBoss(Level& _level, const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher), level(_level) { 
	_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(SlimeBoss::onCollisionBeginEvent));
	this->stateMachine.setCurrentState(make_unique<SlimeBossNormalState>(), *this);
	this->stateMachine.setGlobalState(make_unique<SlimeBossGlobalState>(), *this);
}

/// @brief 
/// Checks whether should hit himself or do damage to the player
/// @param OnCollisionBeginEvent
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

			if (this->player->getObjectId() == otherEntity->getObjectId()) { this->doDamage(); }
		}
		else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity->getObjectId()) { this->doDamage(); }
		}
	}
	return false;
}

/// @brief 
/// SpawnSlime
void SlimeBoss::spawnEnemies() {
	int startingId = 99999;
	int startingTextureId = 99999;

	this->createSlime(startingId++, startingTextureId, 3261, 2307);

	startingTextureId = 99999 + 10;
	this->createSlime(startingId++, startingTextureId, 3471, 2307);

	startingTextureId = 99999 + 20;
	this->createSlime(startingId++, startingTextureId, 4419, 2307);


	startingTextureId = 99999 + 30;
	this->createSlime(startingId++, startingTextureId, 4649, 2307);
	level.restartPhysics();
}

/// @brief 
/// Adds new slime to the level
void SlimeBoss::createSlime(int id, int startingTextureId, float x, float y) {
	shared_ptr<Slime> slime1 = shared_ptr<Slime>(new Slime(id, level.getEventDispatcher()));
	slime1->setPositionX(x);
	slime1->setPositionY(y);
	slime1->setHeight(37);
	slime1->setWidth(37);
	slime1->setPlayer(this->player);
	slime1->setTotalHealth(3);
	slime1->setCurrentHealth(3);
	slime1->setFriction(0);
	slime1->setDensity(50000);
	slime1->setJumpHeight(15);
	slime1->setRestitution(0);
	slime1->setSpeed(4);
	auto result = slime1->buildSpritemap(startingTextureId);
	map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
	while (it != result.end())
	{
		slime1->registerSprite(it->first, it->second);
		it++;
	}
	slime1->changeToState(0);
	level.addNewObjectToLayer(4, slime1, true, false);
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
		this->level.changeToScene(true, "ChapterThree");
		return;
	}

	// Differences are calculated from the middle position of the object
	float xPositionDifference = abs((player->getPositionX() + player->getWidth() / 2) - (this->getPositionX() + this->getWidth() / 2));
	float yPositionDifference = abs((player->getPositionY() + player->getHeight() / 2) - (this->getPositionY() + this->getHeight() / 2));

	// Distance is calculated using the Pythagorean theorem from the middle of both objects
	float distanceFromPlayer = sqrt(pow(xPositionDifference, 2) + pow(yPositionDifference, 2));

	// Direction is based on the x position of the player
	Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;

	bool positionedOnGround = this->getYAxisVelocity() == 0;

	if (positionedOnGround) {
		if (!jumping) {
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
			jumping = true;
		}
	}

	if (jumping) {
		jumpTimer += deltaTime;
		if (jumpTimer < (jumpSpeedTimer / 2)) {
			changeToState(SpriteState::ACTION_2);
		}
		else if (jumpTimer >= (jumpSpeedTimer / 2) && jumpTimer < jumpSpeedTimer) {
			changeToState(SpriteState::ACTION_1);
		}
		if (jumpTimer >= jumpSpeedTimer) {
			changeToState(SpriteState::ACTION_3);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
			jumpTimer = 0;
			jumping = false;
		}
	}
	stateMachine.update(*this);
}

/// @brief
/// Builds the spritemap for the SlimeBoss
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