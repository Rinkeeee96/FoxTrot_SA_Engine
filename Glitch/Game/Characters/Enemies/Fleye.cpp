#include "pch.h"
#include "Fleye.h"

void Fleye::onUpdate() {
	if (setup) {
		startY = this->getPositionY();
		setup = false;
	}

	float diff = player->getPositionX() - this->getPositionX();

	float fleyeMiddleX = this->getPositionX() + (this->getWidth() / 2);

	bool playerIsInRange = (diff < RANGE&& diff >(RANGE * -1));
	bool playerIsLowerThanMe = this->getPositionY() < player->getPositionY();
	bool playerIsWithinXLevelRange = (fleyeMiddleX >= player->getPositionX()) && (fleyeMiddleX <= (player->getPositionX() + player->getWidth()));

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