#pragma once
#include <api.h>
#include "Game/Characters/ICharacter.h"
#include "Game/Characters/Player/Player.h"

class BaseTrigger : public Drawable
{
public:
	BaseTrigger() : Drawable() { }
	BaseTrigger(const int _id) : Drawable(_id, false) {
		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BaseTrigger::onCollisionBegin));
	}
	virtual ~BaseTrigger() { }

	virtual bool onCollisionBegin(Event& event) = 0;
	virtual BaseTrigger* clone(const int id) = 0;
private:
};