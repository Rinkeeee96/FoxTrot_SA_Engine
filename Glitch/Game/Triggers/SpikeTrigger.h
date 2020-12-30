#pragma once
#include "Game/Triggers/BaseTrigger.h"

/// @brief Class for spike trigger, base class BaseTrigger
class SpikeTrigger : public BaseTrigger
{
public:
	SpikeTrigger(EventDispatcher& _dispatcher) : BaseTrigger(_dispatcher) { }
	SpikeTrigger(const int _id, EventDispatcher& _dispatcher) : BaseTrigger(_id, _dispatcher) { }

	shared_ptr<BaseTrigger> clone(const int id) override { return shared_ptr<BaseTrigger>(new SpikeTrigger(id, dispatcher)); }

	void onUpdate(float deltaTime) override {}

	/// @brief Is called when the player collides with a Spike trigger trigger and kills player when not in god state
	/// @param event 
	/// @return 
	bool onCollisionBegin(const Event& event) override {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

		if (shared_ptr<Player> character = dynamic_pointer_cast<Player>(collisionEvent.getObjectOne())) {
			if (typeid(character->getStateMachine().getCurrentState()).name() != typeid(GodState).name()) {
				character->kill();
			}
		}
		else if (shared_ptr<Player> character = dynamic_pointer_cast<Player>(collisionEvent.getObjectTwo())) {
			if (typeid(character->getStateMachine().getCurrentState()).name() != typeid(GodState).name()) {
				character->kill();
			}
		}
		return false;
	}
};