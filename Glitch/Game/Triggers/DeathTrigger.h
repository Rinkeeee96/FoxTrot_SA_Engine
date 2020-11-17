#pragma once
#include "Game/Triggers/TriggerBase.h"

class DeathTrigger : public TriggerBase
{
public:
	DeathTrigger() : TriggerBase() { }
	DeathTrigger(const int _id) : TriggerBase(_id) { }

	virtual TriggerBase* clone(const int id) override { return new DeathTrigger(id); }

	void onUpdate() override {}

	virtual bool onCollisionBegin(Event& event) override {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
		if (collisionEvent.GetObjectOne().getObjectId() != this->getObjectId() && collisionEvent.GetObjectTwo().getObjectId() != this->getObjectId()) return false;

		Object& objectOne = collisionEvent.GetObjectOne();
		Object& objectTwo = collisionEvent.GetObjectOne();

		if (ICharacter* d = dynamic_cast<ICharacter*>(&objectOne)) d->setIsDead(true);
		else if (ICharacter* d = dynamic_cast<ICharacter*>(&objectTwo)) d->setIsDead(true);
	}
};