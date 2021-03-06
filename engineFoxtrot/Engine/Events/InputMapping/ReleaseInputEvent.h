#pragma once
#include "Events/Event.h"
/// @brief
/// ReleaseInputEvent is fired when input capturing is done and events should be released again 
/// this event is intended to free all events from propegating through the engine
class ReleaseInputEvent : public Event
{
public:	
	ReleaseInputEvent() = default;
	EventType getEventType() const override { return EventType::ReleaseInput; }
	const char* getName() const override { return "Release input"; }
};