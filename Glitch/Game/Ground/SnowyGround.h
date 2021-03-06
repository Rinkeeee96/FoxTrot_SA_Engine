#pragma once
#include "Game/Ground/IGround.h"
#include <Game/Characters/Player/Player.h>

/// @brief 
/// "Snowy" ground class
class SnowyGround : public IGround {
private:
	EventDispatcher& dispatcher;
public:
	SnowyGround(EventDispatcher& _dispatcher, const int id) : IGround(id), dispatcher{ _dispatcher } {
		dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(SnowyGround::onCollisionBeginEvent));
	}

	/// @brief 
	/// Sets friction of player to 6 when collision begins
	/// @param OnCollisionBeginEvent
	bool onCollisionBeginEvent(const Event& event) {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getObjectId()];

		if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
			if(collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
				shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

				if (Player* player = dynamic_cast<Player*>(otherEntity.get())) {
					player->setFriction(6.0f);
					UpdatePhysicsBodyEvent e{ *player };
					dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(e);
				}
			}
			else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
				shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

				if (Player* player = dynamic_cast<Player*>(otherEntity.get())) {
					player->setFriction(6.0f);
					UpdatePhysicsBodyEvent e{ *player };
					dispatcher.dispatchEvent<UpdatePhysicsBodyEvent>(e);
				}
			}
		}
		return true;
	}

	virtual void onUpdate(float deltaTime) override {
	};
};