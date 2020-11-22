#pragma once
#include "MouseButtonEvent.h"
#include "Events/Codes/MouseCodes.h"

/// @brief
/// MouseButtonPressedEvent is triggerd when a mouse button is pressed.  Derived class of MouseButtonEvent.
class MouseButtonPressed : public MouseButtonEvent
{
public:
	MouseButtonPressed(MouseCode code) : MouseButtonEvent(code) {}
	/// @brief
	/// MouseButtonPressed to string
	/// @return string with the realesed button
	string ToString() const override
	{
		stringstream stream;
		stream << "MouseButtonPressedEvent: " << (int)button;
		auto string = stream.str();
		return string;
	}
};
