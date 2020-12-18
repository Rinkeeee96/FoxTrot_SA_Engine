#pragma once
#include <ostream>
#include <sstream>
#include "EventType.h"
using namespace std;

/// @brief
	/// Abstract event class. Multiple events have this class as a super class
class Event
{
public:
	virtual ~Event() = default;

	bool Handled = false;
	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	virtual EventType getEventType() const = 0;
	/// @brief
	/// Returns the name of a specific event
	virtual const char* getName() const = 0;

	/// @brief
	/// Returns the name of the event
	virtual string toString() const { return getName(); }
};

inline ostream& operator<<(ostream& osStream, const Event& event)
{
	return osStream << event.toString();
}
