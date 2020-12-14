#pragma once
/// @brief
/// EventType enum all the derived event types that can be fired as an enum
enum class EventType
{
	None = 0,
	ToggleLayer,
	TogglePause,
	// -- input capturing events ---
	CaptureInput,
	ReleaseInput,

	// -- window events -----
	WindowResize, 
	WindowFocus, 
	WindowLostFocus, 
	WindowMoved,
	// -- key events -----
	KeyPressed, 
	KeyReleased, 
	KeyTyped,
	// -- mouse events -----
	MouseScrolled,
	MouseButtonPressed, 
	MouseButtonReleased, 
	MouseMoved, 

	Action,
	CollisionEnd,
	CollisionBegin,

	ObjectStop
};
