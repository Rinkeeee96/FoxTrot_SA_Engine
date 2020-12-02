#pragma once
class EventDispatcher;
class ICommand
{
protected:
	bool enabled;
public:
	virtual bool isEnabled() { return enabled; }
	virtual void execute(EventDispatcher& dispatcher) = 0;
};