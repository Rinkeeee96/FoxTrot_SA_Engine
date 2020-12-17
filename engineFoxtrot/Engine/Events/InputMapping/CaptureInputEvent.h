#pragma once
#include "Events/Event.h"
#include "Events/Codes/KeyCodes.h"
#include "Events/Codes/MouseCodes.h"

/// @brief
/// CaptureInputEvent is fired when input capturing is required 
/// (e.g for keymapping or other input events requiring the user to preform mulitple inputs)
/// this event is intended to stop ALL Keyboard and mouseclick events from propegating through the engine
class CaptureInputEvent : public Event
{
public:
	/// @brief 
	/// Constructor for capturing keyboard events
	/// @param KeyCode
	/// Keycode to be captured by the capture event
	CaptureInputEvent(const KeyCode& _keycode) : pressedKeyboardKey{ &_keycode } {};
	/// @brief 
	/// Constructor for capturing mouse code events
	/// @param MouseCode
	/// MouseCode to be captured by the capture event
	CaptureInputEvent(const MouseCode& _mouseCode) : pressedMouseButton{ &_mouseCode } {};

	EventType getEventType() const override { return EventType::CaptureInput; }
	const char* getName() const override { return "Capture input"; }

private:
	const KeyCode* pressedKeyboardKey;
	const MouseCode* pressedMouseButton;
};