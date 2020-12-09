#pragma once
#include "Events/Event.h"

/// @brief
/// MouseMoved event is triggered when the mouse is moved. Derived class of Event.
class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(const float _x, const float _y) : xPosition{ _x }, yPosition{ _y } {};

	/// @brief
	/// Gets the new X coords of the mouse relative to screen
	/// @return float new X 
	const float getX() { return xPosition; }

	/// @brief
	/// Gets the new Y coords of the mouse relative to screen
	/// @return float new Y 
	const float getY() { return yPosition; }

	/// @brief
	/// MouseButtonPressed to string
	/// @return string with the realesed button
	string toString() const override
	{
		stringstream stream;
		stream << "MouseMovedEvent: " << xPosition << ", " << yPosition;
		return stream.str();
	}



private:
	const float xPosition, yPosition;

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::MouseMoved; }
	/// @brief
	/// Returns the name of the event
	const char* getName() const override { return "MouseMovedEvent"; }
};
