#pragma once
#include <api.h>
#include "Engine/SceneManager/Objects/Object.h"
#include "Game/Characters/ICharacter.h"
#include "Game/Characters/Player/Player.h"

class TriggerBase : public Object
{
public:
	// TODO Fix when merged in develop
	TriggerBase() : Object() { }
	TriggerBase(const int _id) : Object(_id) { 
		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(TriggerBase::onCollisionBegin));
	}
	virtual ~TriggerBase() { }

	virtual bool onCollisionBegin(Event& event) = 0;
	virtual TriggerBase* clone(const int id) = 0;
private:

};