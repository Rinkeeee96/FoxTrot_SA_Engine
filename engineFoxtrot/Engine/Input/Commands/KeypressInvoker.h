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
	API void registerCommand(KeyCode code, ICommand* command);

	/// @brief
	/// Update the keycode that is set to this command
	/// @param code
	/// The new keycode for the command in the map
	/// @param command
	/// A shared pointer to the command which needs to be updated
	API virtual void updateCommand(KeyCode code, ICommand* command);

	/// @brief
	/// Delete a command registered to the given keycode
	API void deleteCommandThatBelongsTo(const KeyCode& code);

	/// @brief
	/// Handle commands placed in the command queue each frame
	API void executeCommandQueue(EventDispatcher& dispatcher);

	/// @brief
	/// Attempts to execute a command for a given keycode,
	/// fails silently when no bind is registered to prevent unwanted exceptions
	/// @param code
	/// Keycode for the to execute command
	API void enqueueCommand(const KeyCode& code);

protected:
	API bool isRegistered(const ICommand& command);
	API bool isRegistered(const KeyCode& keyCode);
private:
	unordered_map<KeyCode, ICommand*> commands;
	queue<KeyCode> executionQueue;
};