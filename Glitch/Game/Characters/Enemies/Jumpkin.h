#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

#define HORIZONTAL_RANGE 900
#define VERTICAL_RANGE 100

/// @brief 
/// Slime class with correspondending AI logic
class Jumpkin : public IEnemy {
public:
	Jumpkin() : IEnemy() {}
	Jumpkin(const int id) : IEnemy(id) {
		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Jumpkin::onCollisionBeginEvent));
	}

	bool onCollisionBeginEvent(Event& event) {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
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
					this->player->kill();
				}
			}
			else if (collisionEvent.getObjectTwo().getObjectId() == this->getObjectId()) {
				Object& otherEntity = collisionEvent.getObjectOne();

				if (this->player->getObjectId() == otherEntity.getObjectId()) {
					this->player->kill();
				}
			}
		}
		return false;
	}

	void onUpdate() override {
		float xDiff = player->getPositionX() - this->getPositionX();
		float yDiff = player->getPositionY() - this->getPositionY();
		bool playerIsInRangeHorizontally = (xDiff < HORIZONTAL_RANGE && xDiff >(HORIZONTAL_RANGE * -1));
		bool playerIsInRangeVertically = (yDiff < VERTICAL_RANGE && yDiff >(VERTICAL_RANGE * -1));
		Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;

		bool positionedOnGround = this->getYAxisVelocity() == 0;
		if (positionedOnGround && playerIsInRangeHorizontally && playerIsInRangeVertically) {
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
		}
	};

	ICharacter* clone(int id) override { return new Jumpkin(id); }
};