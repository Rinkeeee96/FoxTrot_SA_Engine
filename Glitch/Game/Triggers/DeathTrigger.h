#pragma once
#include "Game/Triggers/BaseTrigger.h"

/// @brief Class for death trigger
class DeathTrigger : public BaseTrigger
{
public:
	DeathTrigger(EventDispatcher& _dispatcher) : BaseTrigger(_dispatcher) { }
	DeathTrigger(const int _id, EventDispatcher& _dispatcher) : BaseTrigger(_id, _dispatcher) { }

	BaseTrigger* clone(const int id) override { return new DeathTrigger(id, dispatcher); }

	void onUpdate(float deltaTime) override {}

	/// @brief Is called when the player collides with a death trigger
	/// @param event 
	/// @return 
	bool onCollisionBegin(const Event& event) override {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

		if (ICharacter* character = dynamic_cast<ICharacter*>(&collisionEvent.getObjectOne())) {
			character->kill(); 
			return true;
		}
		else if (ICharacter* character = dynamic_cast<ICharacter*>(&collisionEvent.getObjectTwo())) {
			character->kill(); 
			return true;
		}
		return false;
	}
};