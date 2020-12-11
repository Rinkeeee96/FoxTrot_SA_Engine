#pragma once

class EventDispatcher;

/// @brief Interface for Subsystems that use the eventDispatcher
class API ISubsystem {
public:
	virtual void start(EventDispatcher& dispatcher) = 0; // set dispatcher
	virtual void update() = 0; // update
	virtual void shutdown() = 0; // delete

	// optional pause methods with them defaulting to a non pauseable state
	virtual bool isPaused() { return paused; }

protected:
	bool paused = false;
};
