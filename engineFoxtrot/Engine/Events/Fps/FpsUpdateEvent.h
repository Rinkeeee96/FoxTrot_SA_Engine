#pragma once
#include "Events/Event.h"
#include "Fps/FrameData.h"

/// @brief
/// An event fired when the user toggles the fps counter using the set button
class FpsUpdateEvent : public Event
{
public:
	FpsUpdateEvent() {}

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType GetEventType() const override { return EventType::Action; }
	/// @brief
	/// Returns the name of the event
	const char* GetName() const override { return "Fps update"; }
};