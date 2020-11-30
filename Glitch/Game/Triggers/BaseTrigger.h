#pragma once
#include <api.h>
#include "Game/Characters/ICharacter.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Levels/Level.h"

class BaseTrigger : public Object
{
public:
	BaseTrigger() : Object() { }
	BaseTrigger(const int _id) : Object(_id, false) {
		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BaseTrigger::onCollisionBegin));
	}
	virtual ~BaseTrigger() { }

	virtual bool onCollisionBegin(Event& event) = 0;
	virtual BaseTrigger* clone(const int id) = 0;
private:
};