#pragma once
#include "Game/Triggers/BaseTrigger.h"

/// @brief Class for death trigger, base class BaseTrigger
class DeathTrigger : public BaseTrigger
{
public:
	DeathTrigger(EventDispatcher& _dispatcher) : BaseTrigger(_dispatcher) { }
	DeathTrigger(const int _id, EventDispatcher& _dispatcher) : BaseTrigger(_id, _dispatcher) { }

	shared_ptr<BaseTrigger> clone(const int id) override { return shared_ptr<BaseTrigger>(new DeathTrigger(id, dispatcher)); }

	void onUpdate(float deltaTime) override {}

	/// @brief Is called when the player collides with a death trigger
	/// @param event 
	/// @return 
	bool onCollisionBegin(const Event& event) override {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

		if (shared_ptr<ICharacter> character = dynamic_pointer_cast<ICharacter>(collisionEvent.getObjectOne())) character->kill();
		else if (shared_ptr<ICharacter> character = dynamic_pointer_cast<ICharacter>(collisionEvent.getObjectTwo())) character->kill();
		return false;
	}
};