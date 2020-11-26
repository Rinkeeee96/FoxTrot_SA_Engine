#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

/// @brief 
/// Slime class with correspondending AI logic
class Fleye : public IEnemy {
public:
	Fleye() : IEnemy() {}
	Fleye(const int id) : IEnemy(id) {
		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Fleye::onCollisionBeginEvent));
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
		bool playerIsInRange = player->getPositionX() >= this->getPositionX() - this->getWidth() &&
			player->getPositionX() <= this->getPositionX() + this->width;
		bool playerIsBelowMe = (player->getPositionY() + player->getHeight()) >= this->getPositionY();

		bool positionedOnGround = this->getYAxisVelocity() == 0;
		if(positionedOnGround)
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));

		if (playerIsInRange && playerIsBelowMe && !positionedOnGround){
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::DOWN, this->getObjectId()));
		}
	};

	ICharacter* clone(int id) override { return new Fleye(id); }
};