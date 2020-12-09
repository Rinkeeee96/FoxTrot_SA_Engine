#pragma once

class EventDispatcher;

/// <summary>
/// ISybsystem is a class containing the enforced methods where startup/shutdown boilerplate is desired
/// each method represents an action each subsequent subsystem must implement.
/// </summary>
class ISubsystem {
public:
	virtual void start(EventDispatcher& dispatcher) = 0; // set dispatcher
	virtual void update() = 0; // update
	virtual void shutdown() = 0; // delete

	// optional pause methods with them defaulting to a non pauseable state
	virtual bool isPaused() { return paused; }

protected:
	bool paused = false;
};
