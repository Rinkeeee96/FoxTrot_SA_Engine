#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

#define HORIZONTAL_RANGE 900
#define VERTICAL_RANGE 150

//TODO Use deltaTime
#define JUMP_ANIMATION_TIME 100

/// @brief 
/// Slime class with correspondending AI logic
class Jumpkin : public IEnemy {
public:
	Jumpkin(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) {}
	Jumpkin(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Jumpkin::onCollisionBeginEvent));
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
		float xDiff = player->getPositionX() - this->getPositionX();
		float yDiff = player->getPositionY() - this->getPositionY();
		bool playerIsInRangeHorizontally = (xDiff < HORIZONTAL_RANGE&& xDiff >(HORIZONTAL_RANGE * -1));
		bool playerIsInRangeVertically = (yDiff < VERTICAL_RANGE&& yDiff >(VERTICAL_RANGE * -1));
		Direction direction = player->getPositionX() < this->positionX ? Direction::LEFT : Direction::RIGHT;
		bool positionedOnGround = this->getYAxisVelocity() == 0;

		if (positionedOnGround && playerIsInRangeHorizontally && playerIsInRangeVertically) {
			if (!jumping) {
				EventSingleton::get_instance().dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
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
				EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
				EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(direction, this->getObjectId()));
				jumpTimer = 0;
				jumping = false;
			}
		}

		if (!playerIsInRangeHorizontally) {
			changeToState(SpriteState::DEFAULT);
			EventSingleton::get_instance().dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
		}

		if (!playerIsInRangeHorizontally) {
			changeToState(SpriteState::DEFAULT);
			dispatcher.dispatchEvent<ObjectStopEvent>((Event&)ObjectStopEvent(this->getObjectId(), false));
		}
	};

	ICharacter* clone(int id) override { return new Jumpkin(id); }

private:
	int jumpTimer = 0;
	bool jumping = false;
};