#pragma once
class EventDispatcher;
class ICommand
{
public:
	ICommand(string _identifier) : identifier{ _identifier } {}

	virtual void execute(EventDispatcher& dispatcher) = 0;
	const string& getIdentifier() { return identifier; }
private:
	const string identifier;
};