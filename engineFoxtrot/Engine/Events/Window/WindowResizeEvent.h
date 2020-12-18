#pragma once
#include "Events/Event.h"

/// @brief
/// WindowResizedEvent is fired when the window is resized. Derived class of event. 
class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int width, int height)
		: m_Width(width), m_Height(height) {}

	/// @brief
	/// Gets the width of the resized screen
	/// @return int new width of screen
	uint32_t getWidth() const { return m_Width; }

	/// @brief
	/// Gets the height of the resized screen
	/// @return int new height of screen
	uint32_t getHeight() const { return m_Height; }

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::WindowResize; }
	
	/// @brief
	/// Get the name of an event
	/// @returns the name of the event
	const char* getName() const override { return "Window close"; }

	/// @brief
	/// Event to string
	/// @return string with the width and height
	string toString() const override
	{
		stringstream stream;
		stream << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return stream.str();
	}
private:
	unsigned int m_Width, m_Height;
};