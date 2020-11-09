#pragma once
#include "Events/Event.h"
#include <SceneManager\SpriteObject.h>

/// @brief
/// Video load sprite event
class VideoLoadSpriteEvent : public Event
{
public:
	VideoLoadSpriteEvent(const SpriteObject& object) : spriteObject{ object } {};

	/// @brief
	/// Spriteobject that needs be registerd
	/// @returns SpriteObject
	const SpriteObject& GetSpriteObject() { return spriteObject; }

	/// @brief
	/// VideoLoadSpriteEvent to string
	/// @return string with key code released
	std::string ToString() const override
	{
		std::stringstream stream;
		stream << "Load sprite : " << spriteObject.getFileName();
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
	const SpriteObject& spriteObject;
};
#pragma once
