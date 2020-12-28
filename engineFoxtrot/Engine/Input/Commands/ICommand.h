#pragma once
#include "stdafx.h"
class EventDispatcher;
class ICommand
{
public:
	/// @param _freezeOnPause
	/// this paramter controls whether the command should be deactivated
	/// in the "pause" state, defaults to true to enforce a freezed state if not overridden
	/// @param _identifier
	/// this is the identifier given to this command, for identification purposes which require
	/// identification to know what command this is
	API ICommand(string _identifier, bool _freezeOnPause = true) : identifier{ _identifier }, 
		freezeOnPause{ _freezeOnPause } {}

	/// @brief
	/// Execute the command 
	/// @param dispatcher 
	/// the current dispatcher assigned to a scene
	API virtual void execute(EventDispatcher& dispatcher) = 0;
	API const string& getIdentifier() { return identifier; }
	
	/// @brief
	/// Returns whether this command can execute in the "pause" state
	API bool canExecuteOnPause() { return ! freezeOnPause; }
private:
	/// @brief
	/// the identifier given to this command by the builder
	/// this is used for identification in the invoker
	const string identifier;
	/// @brief
	/// this determines whether the command can be executed in the "paused" state
	const bool freezeOnPause;
};