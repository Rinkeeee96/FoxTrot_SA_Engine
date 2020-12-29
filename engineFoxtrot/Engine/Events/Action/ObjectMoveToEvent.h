#pragma once
#include "Events/Event.h"

/// @brief
/// AppTickEvent is fired when a tick happened in the engine. Derived class of event. 
class ObjectMoveToEvent : public Event
{
public:
	ObjectMoveToEvent(Object& _object, float _x, float _y) : object{ _object }, x{ _x }, y{ _y } {};

	Object& getObject() const { return object; }
	float getMoveToX() const { return x; }
	float getMoveToY() const { return y; }

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::ObjectMoveTo; }

	/// @brief
	/// Returns the name of the event
	const char* getName() const override { return "Move to Event"; }
private:
	Object& object;
	float x = 0;
	float y = 0;
	float speed = 0;
};