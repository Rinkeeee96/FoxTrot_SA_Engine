#pragma once
#include "Engine/SceneManager/Objects/Object.h"
#include "Game/Characters/ICharacter.h"
#include <api.h>


class TriggerBase : public Object
{
public:
	// TODO Fix when merged in develop
	TriggerBase() : Object(-1) { }
	TriggerBase(const int _id) : Object(_id) { 
		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(TriggerBase::onCollisionBegin));
	}
	virtual ~TriggerBase() { }

	virtual bool onCollisionBegin(Event& event) = 0;
	virtual TriggerBase* clone(const int id) = 0;
private:

};

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

class WinTrigger : public TriggerBase
{
public:
	WinTrigger() : TriggerBase() { }
	WinTrigger(const int _id) : TriggerBase(_id) { }

	virtual TriggerBase* clone(const int id) override { return new WinTrigger(id); }

	void onUpdate() override {}

	virtual bool onCollisionBegin(Event& event) override {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
		if (collisionEvent.GetObjectOne().getObjectId() != this->getObjectId() && collisionEvent.GetObjectTwo().getObjectId() != this->getObjectId()) return false;

		Object& objectOne = collisionEvent.GetObjectOne();
		Object& objectTwo = collisionEvent.GetObjectOne();

		// TODO if player fire win event
		if (ICharacter* d = dynamic_cast<ICharacter*>(&objectOne)) {

		}
		else if (ICharacter* d = dynamic_cast<ICharacter*>(&objectTwo)) {
			
		}
	}
};