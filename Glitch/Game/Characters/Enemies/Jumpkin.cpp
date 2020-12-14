#include "pch.h"
#include "Jumpkin.h"

/// @brief
/// Checks if the player is within range and acts accordingly
/// If the player is in range horizontally and vertically, the Jumpkin will move towards the player by jumping
void Jumpkin::onUpdate() {
	// Differences are calculated from the middle position of the object
	float xPositionDifference = abs((player->getPositionX() + player->getWidth() / 2) - (this->getPositionX() + this->getWidth() / 2));
	float yPositionDifference = abs((player->getPositionY() + player->getHeight() / 2) - (this->getPositionY() + this->getHeight() / 2));

	// Distance is calculated using the Pythagorean theorem from the middle of both objects
	float distanceFromPlayer = sqrt(pow(xPositionDifference, 2) + pow(yPositionDifference, 2));

	// Jumpkin's vertical range is calculated separately from distance to ensure it doesn't follow the player when there are multiple layers of height to the level (lvl3)
	bool playerIsInRange = distanceFromPlayer <= JUMPKIN_HORIZONTAL_RANGE;

	// Checks if the Jumpkin in in range vertically
	bool playerIsInRangeVertically = (yPositionDifference < JUMPKIN_VERTICAL_RANGE && yPositionDifference >(JUMPKIN_VERTICAL_RANGE * -1));
	
	// Direction is based on the x position of the player
	Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;

	bool positionedOnGround = this->getYAxisVelocity() == 0;

	if (positionedOnGround && playerIsInRange && playerIsInRangeVertically) {
		if (!jumping) {
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
			jumping = true;
		}
	}

	if (jumping) {
		jumpTimer++;
		if (jumpTimer == JUMPKIN_JUMP_ANIMATION_TIME / 2) {
			changeToState(direction == Direction::LEFT ? SpriteState::ACTION_LEFT_1 : SpriteState::ACTION_RIGHT_1);
		}
		if (jumpTimer == JUMPKIN_JUMP_ANIMATION_TIME) {
			changeToState(direction == Direction::LEFT ? SpriteState::ACTION_LEFT_3 : SpriteState::ACTION_RIGHT_3);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
			jumpTimer = 0;
			jumping = false;
		}
	}

	if (!playerIsInRange) {
		changeToState(SpriteState::DEFAULT);
		dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
	}
}

/// @brief
/// Builds the spritemap for the Jumpkin
map<SpriteState, shared_ptr<SpriteObject>> Jumpkin::buildSpritemap(int textureId) {
	std::map<SpriteState, shared_ptr<SpriteObject>> spriteMap;

	auto jumpkinDefault = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_default.png"));
	auto jumpkinActionLeft1 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_left_1.png"));
	auto jumpkinActionLeft2 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH_SHORT, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_left_2.png"));
	auto jumpkinActionLeft3 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH_SHORT, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_left_3.png"));
	auto jumpkinActionRight1 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_right_1.png"));
	auto jumpkinActionRight2 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH_SHORT, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_right_2.png"));
	auto jumpkinActionRight3 = shared_ptr<SpriteObject>(new SpriteObject(textureId++, JUMPKIN_SPRITE_HEIGHT, JUMPKIN_SPRITE_WIDTH_SHORT, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_right_3.png"));

	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::DEFAULT, jumpkinDefault));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_LEFT_1, jumpkinActionLeft1));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_LEFT_2, jumpkinActionLeft2));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_LEFT_3, jumpkinActionLeft3));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_RIGHT_1, jumpkinActionRight1));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_RIGHT_2, jumpkinActionRight2));
	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::ACTION_RIGHT_3, jumpkinActionRight3));

	return spriteMap;
}