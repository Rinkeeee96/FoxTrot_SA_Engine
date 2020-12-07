#pragma once
class EventDispatcher;
class ICommand
{
public:
	API ICommand(string _identifier) : identifier{ _identifier } {}

	/// @brief
	/// Execute the command 
	/// @param dispatcher 
	/// the current dispatcher assigned to a scene
	API virtual void execute(EventDispatcher& dispatcher) = 0;
	API const string& getIdentifier() { return identifier; }
private:
	/// @brief
	/// the identifier given to this command by the builder
	/// this is used for identification in the invoker
	const string identifier;
};