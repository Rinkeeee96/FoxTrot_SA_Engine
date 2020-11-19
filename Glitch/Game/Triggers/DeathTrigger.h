#pragma once
#include "Game/Triggers/BaseTrigger.h"

class DeathTrigger : public BaseTrigger
{
public:
	DeathTrigger() : BaseTrigger() { }
	DeathTrigger(const int _id) : BaseTrigger(_id) { }

	virtual BaseTrigger* clone(const int id) override { return new DeathTrigger(id); }

	void onUpdate() override {}

	virtual bool onCollisionBegin(Event& event) override {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

		if (ICharacter* character = dynamic_cast<ICharacter*>(&collisionEvent.getObjectOne())) character->setHealth(0);
		else if (ICharacter* character = dynamic_cast<ICharacter*>(&collisionEvent.getObjectTwo())) character->setHealth(0);
	}
};