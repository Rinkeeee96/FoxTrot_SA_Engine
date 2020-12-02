#pragma once
#include "Events/Codes/KeyCodes.h"
#include "Events/EventDispatcher.h"
#include "ICommand.h"
#include <queue>
class KeypressInvoker
{
public:
	/// @brief
	/// Register keybinds in the invoker for the first time, 
	/// throws exception when trying to register multiple commands under the same binding
	/// @param code
	/// The keycode for the command in the map
	/// @param command
	/// A shared pointer to the command which needs to be registered
	void registerCommands(KeyCode code, unique_ptr<ICommand> command);

	/// @brief
	/// Update the keycode that is set to this command
	/// @param code
	/// The new keycode for the command in the map
	/// @param command
	/// A shared pointer to the command which needs to be updated
	virtual void updateCommand(KeyCode code, unique_ptr<ICommand> command);

	/// @brief
	/// Queue a command for execution by the engine
	void executeCommandQueue(EventDispatcher& dispatcher);

	/// @brief
	/// Attempts to execute a command for a given keycode,
	/// fails silently when no bind is registered to prevent unwanted exceptions
	/// @param code
	/// Keycode for the to execute command
	void executeCommand(KeyCode code);

protected:
	bool isRegistered(unique_ptr<ICommand>& command);
	bool isRegistered(const KeyCode& keyCode);
private:
	// TODO transfer ownership to command invoker from builder via unique_ptr
	unordered_map<KeyCode, unique_ptr<ICommand>> commands;
	queue<KeyCode> executionQueue;
};