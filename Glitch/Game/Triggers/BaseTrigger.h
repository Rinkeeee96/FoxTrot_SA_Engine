#pragma once
#include <api.h>
#include "Game/Characters/ICharacter.h"
#include "Game/Characters/Player/Player.h"

class BaseTrigger : public Object
{
public:
	BaseTrigger(shared_ptr<EventDispatcher> _dispatcher) : dispatcher{ _dispatcher }, Object() { }
	BaseTrigger(const int _id, shared_ptr<EventDispatcher> _dispatcher) : dispatcher{ _dispatcher }, Object(_id, false) {
		(*dispatcher.get()).setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BaseTrigger::onCollisionBegin));
	}
	virtual ~BaseTrigger() { }

	virtual bool onCollisionBegin(const Event& event) = 0;
	virtual BaseTrigger* clone(const int id) = 0;
protected:
	shared_ptr<EventDispatcher> dispatcher;
};