#pragma once
#include "Events/Event.h"
#include "Events\Codes\KeyCodes.h"

/// @brief
/// KeyEvent base class for all key events:
/// Keypressed, KeyReleased, KeyTyped
class KeyEvent : public Event
{
public:
	/// @brief
	/// KeyCode that is pressed
	/// @returns KeyCode
	KeyCode getKeyCode() const { return keycode; }

	virtual const char* getName() const override { return "keyPressed event"; };

	/// @brief
	/// Returns the name of the event
	virtual string toString() const { return getName(); }

	/// @brief
	/// Returns type of the event
	EventType getEventType() const override { return EventType::KeyPressed; }
protected:
	KeyEvent(const KeyCode _keyCode) : keycode{ _keyCode } {};
	KeyCode keycode;
};
