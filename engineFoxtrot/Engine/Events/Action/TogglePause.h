#pragma once
#include "Events/Event.h"
class TogglePauseEvent : public Event
{
public:
	TogglePauseEvent(bool pause) : _isPaused{ pause } {};
	bool isPaused() { return _isPaused; }
private:
	bool _isPaused;

	// Inherited via Event
	virtual EventType GetEventType() const override;
	virtual const char* GetName() const override;
};

EventType TogglePauseEvent::GetEventType() const
{
	return EventType::TogglePause;
}

const char* TogglePauseEvent::GetName() const
{
	return "Toggle pause";
}
