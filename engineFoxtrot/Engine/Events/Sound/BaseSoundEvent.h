#pragma once
#include "Events/Event.h"

#define MAX_VOLUME 128

/// @brief
/// KeyEvent base class for all key events:
/// Keypressed, KeyReleased, KeyTyped
class BaseSoundEvent : public Event
{
public:
	/// @brief
	/// sound identifier
	/// @returns string&
	const std::string& Getidentifier() { return identifier; }

	// @brief
	/// get the sound volume
	/// @returns int
	const int getVolume() { return volume; }

protected:
	BaseSoundEvent(const std::string& _identifier, int _volume) : 
		identifier{ _identifier }, 
		volume{ _volume }
	{};
	const std::string& identifier;
	const int volume;
};
