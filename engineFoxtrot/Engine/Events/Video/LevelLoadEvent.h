#pragma once
#include "Events/Event.h"

/// @brief
/// Video load sprite event
class LevelLoadEvent : public Event
{
public:
	LevelLoadEvent(const string& _level) : level{ _level } {};

	/// @brief
	/// Spriteobject that needs be registerd
	/// @returns SpriteObject
	const string GetLevel() { return level; }

	/// @brief
	/// VideoLoadSpriteEvent to string
	/// @return string with key code released
	std::string ToString() const override
	{
		std::stringstream stream;
		stream << "Load level : " << level;
		return stream.str();
	}

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType GetEventType() const override { return EventType::LoadSprite; }
	/// @brief
	/// Returns the name of the event
	const char* GetName() const override { return "Load Sprite Event"; }

protected:
	const string level;
};
