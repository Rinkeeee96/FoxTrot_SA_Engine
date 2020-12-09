#pragma once
#include "Events/Event.h"


enum class Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

/// @brief
/// AppTickEvent is fired when a tick happened in the engine. Derived class of event. 
class ActionEvent : public Event
{
public:
	ActionEvent(const Direction _direction, int _objectId) : direction{ _direction }, objectId{ _objectId } {};

	Direction getDirection() const { return direction; }
	int getObjectId() const { return objectId; }
	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::Action; }
	/// @brief
	/// Returns the name of the event
	const char* getName() const override { return "Action Event"; }
private:
	int objectId;
	Direction direction;
};