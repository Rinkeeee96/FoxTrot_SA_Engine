#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

#define RANGE 900

/// @brief 
/// Slime class with correspondending AI logic
class Fleye : public IEnemy {
public:
	Fleye(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) { this->setGravity(0); }
	Fleye(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Fleye::onCollisionBeginEvent));
		this->setGravity(0);
	}

	bool onCollisionBeginEvent(const Event& event) {
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

	void onUpdate() override {

		if (setup) {
			startY = this->getPositionY();
			setup = false;
			changeToState(SpriteState::ACTION_LEFT_1);
		}

		float diff = player->getPositionX() - this->getPositionX();

		float fleyeMiddleX = this->getPositionX() + (this->getWidth() / 2);

		bool playerIsInRange = (diff < RANGE&& diff >(RANGE * -1));
		bool playerIsBelowMe = this->getPositionY() < player->getPositionY();
		bool playerIsOnSameXLvl = (fleyeMiddleX >= player->getPositionX()) && (fleyeMiddleX <= (player->getPositionX() + player->getWidth()));

		Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;

		bool positionedOnGround = this->getYAxisVelocity() == 0;
		if (!goingUp && playerIsInRange) {
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
		}
		if (playerIsBelowMe && playerIsOnSameXLvl && !goingUp && this->getYAxisVelocity() == 0) {
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
	};

	map<SpriteState, SpriteObject*> buildSpritemap(int startId) override {
		std::map<SpriteState, SpriteObject*> spriteMap;

		auto fleyeDefault = new SpriteObject(startId++, 42, 42, 1, 200, "Assets/Sprites/Enemies/Fleye/Fleye_idle.png");
		auto fleyeMove = new SpriteObject(startId++, 112, 140, 4, 200, "Assets/Sprites/Enemies/Fleye/Fleye_move.png");

		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, fleyeDefault));
		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_LEFT_1, fleyeMove));

		return spriteMap;
	}

	ICharacter* clone(int id) override { return new Fleye(id, this->dispatcher); }

private:
	bool goingUp = false;
	bool setup = true;
	float startY = 0;
};