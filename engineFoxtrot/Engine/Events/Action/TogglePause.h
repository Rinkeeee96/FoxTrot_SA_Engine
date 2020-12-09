#pragma once
#include "Events/Event.h"
class TogglePauseEvent : public Event
{
public:
	TogglePauseEvent(bool pause) : _isPaused{ pause } {};
	API bool isPaused() { return _isPaused; }
private:
	bool _isPaused;

	// Inherited via Event
	API EventType GetEventType() const override
	{
		return EventType::TogglePause;
	}
	API const char* GetName() const override {
		return "Toggle pause";
	}
};