#pragma once
#include "Events/Event.h"

/// @brief Event for lowering Game speed
class DecreaseGameSpeedEvent : public Event
{
public:

	bool Handled = false;
	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::DecreaseGameSpeed; };
	/// @brief
	/// Returns the name of a specific event
	const char* getName() const override { return "Decrease speed event"; };
};