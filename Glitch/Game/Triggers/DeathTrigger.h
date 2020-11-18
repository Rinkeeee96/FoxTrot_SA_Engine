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

		if (ICharacter* character = dynamic_cast<ICharacter*>(&collisionEvent.GetObjectOne())) character->setIsDead(true);
		else if (ICharacter* character = dynamic_cast<ICharacter*>(&collisionEvent.GetObjectTwo())) character->setIsDead(true);
	}
};