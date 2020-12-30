 #pragma once
#include "Game/Ground/IGround.h"
#include <Game/Characters/Player/Player.h>

/// @brief 
/// "Bouncing" ground class
class BouncingGround : public IGround {
private:
	EventDispatcher& dispatcher;
	Level& level;
public:
	BouncingGround(Level& _level, EventDispatcher& _dispatcher, const int id) : IGround(id), dispatcher{ _dispatcher }, level{ _level } {
		dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BouncingGround::onCollisionBeginEvent));
	}

	/// @brief 
	/// Calls player jump on collision begin
	/// @param OnCollisionBeginEvent
	bool onCollisionBeginEvent(const Event& event) {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getObjectId()];

		if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
			if (collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
				shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

				if (Player* player = dynamic_cast<Player*>(otherEntity.get())) {
					dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, player->getObjectId()));
				}
			}
			else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
				shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

				if (Player* player = dynamic_cast<Player*>(otherEntity.get())) {
					dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, player->getObjectId()));
				}
			}
		}
		return true;
	}

	virtual void onUpdate(float deltaTime) override { };
};