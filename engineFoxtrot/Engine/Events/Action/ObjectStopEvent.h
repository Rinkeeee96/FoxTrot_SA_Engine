#pragma once
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "SceneManager/Objects/Object.h"

/// @brief
/// OnCollisionEvent base class of CollisionEnd and CollisionStart
class ObjectStopEvent : public Event
{
public:
	ObjectStopEvent(int _objectId, bool _stopVertical = false, bool _stopHorizontal = false) :
		objectId{ _objectId }, stopVertical{ _stopVertical }, stopHorizontal{ _stopHorizontal } {};

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::ObjectStop; }

	/// @brief
	/// Returns the name of the event
	const char* getName() const override { return "Object stop"; }

	const int getObjectId() const { return objectId; }
	const bool getStopVertical() const { return stopVertical; }
	const bool getStopHorizontal() const { return stopHorizontal; }
protected:
	int objectId;
	bool stopVertical;
	bool stopHorizontal;
};