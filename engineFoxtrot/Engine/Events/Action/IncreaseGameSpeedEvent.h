#pragma once
#include "Events/Event.h"

/// @brief Event for highering Game speed
class IncreaseGameSpeedEvent : public Event
{
public:

	bool Handled = false;
	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::IncreaseGameSpeed; };
	/// @brief
	/// Returns the name of a specific event
	const char* getName() const override { return "Increase speed event"; };
};