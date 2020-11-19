#pragma once
#include "Events/Sound/BaseSoundEvent.h"

/// @brief
/// AppTickEvent is fired when a tick happened in the engine. Derived class of event. 
class StopSoundEffectEvent : public BaseSoundEvent
{
public:
	StopSoundEffectEvent(const std::string& _file) : BaseSoundEvent(_file) {}

	/// @brief
	/// StopSoundEffectEvent  to string
	/// @return string with sound effect that is stopped
	std::string ToString() const override
	{
		std::stringstream stream;
		stream << "Stop sound effect: " << identifier;
		return stream.str();
	}

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType GetEventType() const override { return EventType::StopEffectEvent; }
	/// @brief
	/// Returns the name of the event
	const char* GetName() const override { return "Action Sound Stop Event"; }
};