#pragma once
#include "Events/Event.h"

/// @brief
/// WindowResizedEvent is fired when the window is resized. Derived class of event. 
class VideoZoomEvent : public Event
{
public:
	VideoZoomEvent(float _scale) : scale(_scale) {}

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	float getScale() const { return scale; }

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::VideoZoom; }
	
	/// @brief
	/// Get the name of an event
	/// @returns the name of the event
	const char* getName() const override { return "Video zoom"; }

	/// @brief
	/// Event to string
	/// @return string with the width and height
	string toString() const override
	{
		return getName();
	}
private:
	float scale;
};