#pragma once

class EventDispatcher;

class ISubsystem {
public:
	virtual void start(EventDispatcher& dispatcher) = 0; // set dispatcher
	virtual void update() = 0; // update
	virtual void shutdown() = 0; // delete
};
