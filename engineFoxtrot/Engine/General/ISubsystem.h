#pragma once

class EventDispatcher;

class ISubsystem {
public:
	virtual void start(EventDispatcher& dispatcher) = 0; // set dispatcher
	virtual void update() = 0; // update
	virtual void shutdown() = 0; // delete

	// optional pause methods with them defaulting to a non pauseable state
	virtual void pause() {};
	virtual bool isPaused() { return false; }
};
