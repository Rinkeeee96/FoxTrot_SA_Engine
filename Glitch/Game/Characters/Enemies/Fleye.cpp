#include "pch.h"
#include "Fleye.h"

void Fleye::onUpdate() {
	if (setup) {
		startY = this->getPositionY();
		setup = false;
	}

	float fleyeMiddleXPosition = this->getPositionX() + this->getWidth() / 2;

	// Differences are calculated from the middle position of the object
	float xPositionDifference = abs((player->getPositionX() + player->getWidth() / 2) - fleyeMiddleXPosition);
	float yPositionDifference = abs((player->getPositionY() + player->getHeight() / 2) - (this->getPositionY() + this->getHeight() / 2));

	// Distance is calculated using the Pythagorean theorem from the middle of both objects
	float distanceFromPlayer = sqrt(abs(pow(xPositionDifference, 2) + pow(yPositionDifference, 2)));

	bool playerIsInRange = distanceFromPlayer <= FLEYE_RANGE;
	bool playerIsLowerThanMe = this->getPositionY() < player->getPositionY();
	bool playerIsWithinXLevelRange = (fleyeMiddleXPosition >= player->getPositionX()) && (fleyeMiddleXPosition <= (player->getPositionX() + player->getWidth()));

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

map<SpriteState, SpriteObject*> Fleye::buildSpritemap(int textureId) {
	std::map<SpriteState, SpriteObject*> spriteMap;

	auto fleyeDefault = new SpriteObject(textureId++, 112, 140, 4, 200, "Assets/Sprites/Enemies/Fleye/Fleye_default.png");

	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, fleyeDefault));

	return spriteMap;
}