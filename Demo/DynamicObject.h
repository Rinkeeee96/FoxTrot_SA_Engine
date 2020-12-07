#pragma once
#include "SpriteState.h"

class DynamicObject : public Drawable
{
public:
	DynamicObject(int id, EventDispatcher& _dispatcher) : Drawable(id, false), dispatcher{_dispatcher} {
		this->setSpeed(6);
		this->setJumpHeight(10);
		this->setDensity(10);
		this->setFriction(0);
		this->setRestitution(0.1f);
		this->setRotatable(false);
		this->setScalable(true);
		this->setScale(1);

		dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(DynamicObject::onKeyPressed));
		dispatcher.setEventCallback<KeyReleasedEvent>(BIND_EVENT_FN(DynamicObject::onKeyReleased));
	}

	bool onKeyReleased(const Event& event);

	bool onKeyPressed(const Event& event);

private:
	EventDispatcher& dispatcher;
	SpriteState state;
};

