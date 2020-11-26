#pragma once
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "SceneManager/Objects/Object.h"

/// @brief
/// OnCollisionEvent base class of CollisionEnd and CollisionStart
class RemoveEvent : public Event
{
public:
	RemoveEvent() {};

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType GetEventType() const override { return EventType::RemoveObject; }
	/// @brief
	/// Returns the name of the event
	const char* GetName() const override { return "Object stop"; }
};