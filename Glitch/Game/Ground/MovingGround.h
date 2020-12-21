#pragma once
#include "Game/Ground/IGround.h"
#include <Game/Characters/Player/Player.h>

#define MIN_HEIGHT 500

/// @brief 
/// "Normal" ground class
class MovingGround : public IGround {
private:
	EventDispatcher& dispatcher;
public:
	MovingGround(EventDispatcher& _dispatcher, const int id) : IGround(id), dispatcher{ _dispatcher } {
		this->staticObject = BodyType::KINEMATIC;
		dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(MovingGround::onCollisionBeginEvent));
	}

	bool onCollisionBeginEvent(const Event& event) {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getObjectId()];

		if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
			if (collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
				shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

				if (Player* player = dynamic_cast<Player*>(otherEntity.get())) {
					player->setDensity(10);
					player->setFriction(0);
					player->setRestitution(0.1f);
					UpdatePhysicsBodyEvent e{ *player };
					dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(e);
				}
			}
			else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
				shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

				if (Player* player = dynamic_cast<Player*>(otherEntity.get())) {
					player->setDensity(10);
					player->setFriction(0);
					player->setRestitution(0.1f);
					UpdatePhysicsBodyEvent e{ *player };
					dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(e);
				}
			}
		}
		return true;
	}
	 
	void setStatic(const bool) override { }

	virtual void onUpdate(float deltaTime) override {
		if (this->getPositionY() - deltaTime * 100 > MIN_HEIGHT) {
			return;
		}
		this->setPositionY(this->getPositionY() - deltaTime * 100);
		UpdatePhysicsBodyEvent e{ *this };
		dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(e);
	};
};