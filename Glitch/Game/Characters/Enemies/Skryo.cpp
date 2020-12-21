#include "pch.h"
#include "Skryo.h"

/// @brief
/// Checks if the player is within range and acts accordingly
/// If the player is below the Skryo, it will swoop down towards the player
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void Skryo::onUpdate(float deltaTime) {
	// Differences are calculated from the middle position of the object
	float xPositionDifference = abs((player->getPositionX() + player->getWidth() / 2) - (this->getPositionX() + this->getWidth() / 2));
	float yPositionDifference = abs((player->getPositionY() + player->getHeight() / 2) - (this->getPositionY() + this->getHeight() / 2));

	// Distance is calculated using the Pythagorean theorem from the middle of both objects
	float distanceFromPlayer = sqrt(pow(xPositionDifference, 2) + pow(yPositionDifference, 2));

	// Jumpkin's vertical range is calculated separately from distance to ensure it doesn't follow the player when there are multiple layers of height to the level (lvl3)
	bool playerIsInRange = distanceFromPlayer <= SKRYO_RANGE;

	// Direction is based on the x position of the player
	Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;

	bool positionedOnGround = this->getYAxisVelocity() == 0;

	if (playerIsInRange && !dashing) {
		dashTimer += deltaTime;
		if (dashTimer >= SKRYO_DASH_COOLDOWN_TIME) {
			dashing = true;
			dashTimer = 0;
		}
	}

	if (dashing) {
		dashTimer += deltaTime;
		if (dashTimer >= (SKRYO_DASH_ANIMATION_TIME / 2) && dashTimer <= SKRYO_DASH_ANIMATION_TIME) {
			changeToState(direction == Direction::LEFT ? SpriteState::ACTION_LEFT_1 : SpriteState::ACTION_RIGHT_1);
		}
		if (dashTimer >= SKRYO_DASH_ANIMATION_TIME) {
			changeToState(direction == Direction::LEFT ? SpriteState::RUN_LEFT : SpriteState::RUN_RIGHT);
			//dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
			this->setYAxisVelocity(100);
			dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(UpdatePhysicsBodyEvent{ *this });
			dashTimer = 0;
			dashing = false;
		}
	}

	if (!playerIsInRange) {
		changeToState(SpriteState::DEFAULT);
		dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
	}
}

/// @brief
/// Builds the spritemap for the Skryo
map<SpriteState, shared_ptr<SpriteObject>> Skryo::buildSpritemap(int textureId) {
	std::map<SpriteState, shared_ptr<SpriteObject>> spriteMap;

	auto skryoDefault = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 35, 35, 1, 200, "Assets/Sprites/Enemies/Skryo/Skryo.png"));
	auto skryoRight = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 35, 35, 16, 200, "Assets/Sprites/Enemies/Skryo/Skryo_right.png"));
	auto skryoLeft = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 35, 35, 16, 200, "Assets/Sprites/Enemies/Skryo/Skryo_left.png"));

	auto skryoAction1Right = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 35, 35, 16, 200, "Assets/Sprites/Enemies/Skryo/Skryo_action_right_1.png"));
	auto skryoAction1Left = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 35, 35, 16, 200, "Assets/Sprites/Enemies/Skryo/Skryo_action_left_1.png"));

	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::DEFAULT, skryoDefault));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::RUN_RIGHT, skryoRight));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::RUN_LEFT, skryoLeft));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_RIGHT_1, skryoAction1Right));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_LEFT_1, skryoAction1Left));

	return spriteMap;
}