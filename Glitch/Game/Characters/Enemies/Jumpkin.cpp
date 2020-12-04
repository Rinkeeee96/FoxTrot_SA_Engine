#include "pch.h"
#include "Jumpkin.h"

bool Jumpkin::onCollisionBeginEvent(const Event& event) {
	auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
	if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
		this->kill();
	}
	else {
		if (collisionEvent.getObjectOne().getObjectId() == this->getObjectId()) {
			Object& otherE = collisionEvent.getObjectTwo();

			if (this->player->getObjectId() == otherE.getObjectId()) {
				this->player->setCurrentHealth(this->player->getCurrentHealth() - 1);
			}
		}
		else if (collisionEvent.getObjectTwo().getObjectId() == this->getObjectId()) {
			Object& otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity.getObjectId()) {
				this->player->setCurrentHealth(this->player->getCurrentHealth() - 1);
			}
		}
	}
	return false;
}

void Jumpkin::onUpdate() {
	float xDiff = player->getPositionX() - this->getPositionX();
	float yDiff = player->getPositionY() - this->getPositionY();
	bool playerIsInRangeHorizontally = (xDiff < HORIZONTAL_RANGE&& xDiff >(HORIZONTAL_RANGE * -1));
	bool playerIsInRangeVertically = (yDiff < VERTICAL_RANGE&& yDiff >(VERTICAL_RANGE * -1));
	Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;
	bool positionedOnGround = this->getYAxisVelocity() == 0;

	if (positionedOnGround && playerIsInRangeHorizontally && playerIsInRangeVertically) {
		if (!jumping) {
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
			jumping = true;
		}
	}

	if (jumping) {
		jumpTimer++;
		if (jumpTimer == JUMP_ANIMATION_TIME / 2) {
			changeToState(direction == Direction::LEFT ? SpriteState::ACTION_LEFT_1 : SpriteState::ACTION_RIGHT_1);
		}
		if (jumpTimer == JUMP_ANIMATION_TIME) {
			changeToState(direction == Direction::LEFT ? SpriteState::ACTION_LEFT_3 : SpriteState::ACTION_RIGHT_3);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
			jumpTimer = 0;
			jumping = false;
		}
	}

	if (!playerIsInRangeHorizontally) {
		changeToState(SpriteState::DEFAULT);
		dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
	}
}

map<SpriteState, SpriteObject*> Jumpkin::buildSpritemap(int textureId) {
	std::map<SpriteState, SpriteObject*> spriteMap;

	auto jumpkinDefault = new SpriteObject(textureId++, 43, 32, 1, 200, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_idle.png");
	auto jumpkinActionLeft1 = new SpriteObject(textureId++, 43, 32, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_left_1.png");
	auto jumpkinActionLeft2 = new SpriteObject(textureId++, 43, 30, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_left_2.png");
	auto jumpkinActionLeft3 = new SpriteObject(textureId++, 43, 30, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_left_3.png");
	auto jumpkinActionRight1 = new SpriteObject(textureId++, 43, 32, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_right_1.png");
	auto jumpkinActionRight2 = new SpriteObject(textureId++, 43, 30, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_right_2.png");
	auto jumpkinActionRight3 = new SpriteObject(textureId++, 43, 30, 1, 400, "Assets/Sprites/Enemies/Jumpkin/Jumpkin_right_3.png");

	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, jumpkinDefault));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_LEFT_1, jumpkinActionLeft1));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_LEFT_2, jumpkinActionLeft2));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_LEFT_3, jumpkinActionLeft3));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_RIGHT_1, jumpkinActionRight1));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_RIGHT_2, jumpkinActionRight2));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_RIGHT_3, jumpkinActionRight3));

	return spriteMap;
}