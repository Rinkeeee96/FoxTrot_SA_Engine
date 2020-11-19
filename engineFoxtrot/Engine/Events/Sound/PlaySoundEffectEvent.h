#pragma once
#include "Events/Sound/BaseSoundEvent.h"

/// @brief
/// AppTickEvent is fired when a tick happened in the engine. Derived class of event. 
class PlaySoundEffectEvent : public BaseSoundEvent
{
public:
	PlaySoundEffectEvent(const std::string& identifier, bool _loop = false, int volume = MAX_VOLUME): loop(_loop), BaseSoundEvent(identifier, volume) {}

	/// @brief
	/// KeyReleasedEvent to string
	/// @return string with key code released
	std::string ToString() const override
	{
		std::stringstream stream;
		stream << "Started Sound: " << identifier;
		return stream.str();
	}

	const bool shouldLoop() { return loop; }

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType GetEventType() const override { return EventType::PlayEffectEvent; }
	/// @brief
	/// Returns the name of the event
	const char* GetName() const override { return "Action Soundeffect start Event"; }
private:
	bool loop;
};