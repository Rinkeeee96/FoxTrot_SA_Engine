#pragma once
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "SceneManager/Objects/Object.h"

/// @brief
/// OnCollisionEvent base class of CollisionEnd and CollisionStart
class ObjectStopEvent : public Event
{
public:
	ObjectStopEvent(int _objectId, bool _stopVertical = false) :
		objectId{ _objectId }, stopVertical{_stopVertical} {};

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType GetEventType() const override { return EventType::ObjectStop; }
	/// @brief
	/// Returns the name of the event
	const char* GetName() const override { return "Object stop"; }

	const int GetObjectId() const { return objectId; }
	const bool GetStopVertical() const { return stopVertical; }
protected:
	int objectId;
	bool stopVertical;
};