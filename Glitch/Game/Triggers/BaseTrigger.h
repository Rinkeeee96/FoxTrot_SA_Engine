#pragma once
#include <api.h>
#include "Game/Characters/ICharacter.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Levels/Level.h"

/// @brief Base class for triggers.
class BaseTrigger : public Object
{
public:
	BaseTrigger(EventDispatcher& _dispatcher) : dispatcher{ _dispatcher }, Object() { }
	BaseTrigger(const int _id, EventDispatcher& _dispatcher) : dispatcher{ _dispatcher }, Object(_id, false) {
		dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BaseTrigger::onCollisionBegin));
	}
	virtual ~BaseTrigger() { }

	virtual bool onCollisionBegin(const Event& event) = 0;
	virtual shared_ptr<BaseTrigger> clone(const int id) = 0;
protected:
	EventDispatcher& dispatcher;
};