#include "pch.h"
#include "Fleye.h"

/// @brief
/// Checks if the player is within range and acts accordingly
/// If the player is below the Fleye, it will swoop down towards the player
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void Fleye::onUpdate(float deltaTime) {
	if (setup) {
		startY = this->getPositionY();
		setup = false;
	}

	float fleyeMiddleXPosition = this->getPositionX() + this->getWidth() / 2;

	// Differences are calculated from the middle position of the object
	float xPositionDifference = abs((player->getPositionX() + player->getWidth() / 2) - fleyeMiddleXPosition);
	float yPositionDifference = abs((player->getPositionY() + player->getHeight() / 2) - (this->getPositionY() + this->getHeight() / 2));

	// Distance is calculated using the Pythagorean theorem from the middle of both objects
	float distanceFromPlayer = (float)sqrt(pow(xPositionDifference, 2) + pow(yPositionDifference, 2));

	// Calculates if the enemy is in range of the player
	bool playerIsInRange = distanceFromPlayer <= FLEYE_RANGE;

	// Checks if the player is lower than the player
	bool playerIsLowerThanMe = this->getPositionY() < player->getPositionY();

	// Checks if the player is within the same X coords as the enemy
	bool playerIsWithinXLevelRange = (fleyeMiddleXPosition >= player->getPositionX()) && (fleyeMiddleXPosition <= (player->getPositionX() + player->getWidth()));

	// Direction is based on the x position of the player
	Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;

	bool positionedOnGround = this->getYAxisVelocity() == 0;
	if (!goingUp && playerIsInRange) {
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
	}
	if (playerIsLowerThanMe && playerIsWithinXLevelRange && !goingUp && this->getYAxisVelocity() == 0) {
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::DOWN, this->getObjectId()));
		goingUp = true;
	}
	else if (goingUp) {
		if (this->getYAxisVelocity() == 0) {
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
		}
		else if (this->getPositionY() <= startY) {
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), true));
			goingUp = false;
		}
	}
}

/// @brief
/// Builds the spritemap for the Fleye
map<SpriteState, shared_ptr<SpriteObject>> Fleye::buildSpritemap(int textureId) {
	std::map<SpriteState, shared_ptr<SpriteObject>> spriteMap;

	auto fleyeDefault = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 112, 140, 4, 200, "Assets/Sprites/Enemies/Fleye/Fleye_default.png"));

	spriteMap.insert(std::pair<SpriteState, shared_ptr<SpriteObject>>(SpriteState::DEFAULT, fleyeDefault));

	return spriteMap;
}