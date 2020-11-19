#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

/// @brief 
/// Slime class with correspondending AI logic
class Slime : public IEnemy {
private:
	bool init = true;
public:
	Slime() : IEnemy() {}
	Slime(const int id) : IEnemy(id) {
		//EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Slime::onCollisionBeginEvent));
	}

	//bool onCollisionBeginEvent(Event& event) {
	//	auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
	//	if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

	//	auto map = collisionEvent.getDirectionMap();
	//	auto collidedDirection = map[this->getObjectId()];


	//	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
	//		// TODO First on init comes here
	//		if (!init)
	//			this->setIsDead(true);
	//		else
	//			init = true;
	//	}
	//	else {
	//		if (collisionEvent.getObjectOne().getObjectId() == this->getObjectId()) {
	//			Object& otherE = collisionEvent.getObjectTwo();

	//			if (this->player->getObjectId() == otherE.getObjectId()) {
	//				this->player->setIsDead(true);
	//			}
	//		}
	//		else if (collisionEvent.getObjectTwo().getObjectId() == this->getObjectId()) {
	//			Object& otherEntity = collisionEvent.getObjectOne();

	//			if (this->player->getObjectId() == otherEntity.getObjectId()) {
	//				this->player->setIsDead(true);
	//			}
	//		}
	//	}
	//	return false;
	//}

	void onUpdate() override {
		//if(this->getYAxisVelocity() == 0) EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
	};

	ICharacter* clone(int id) override { return new Slime(id); }
};