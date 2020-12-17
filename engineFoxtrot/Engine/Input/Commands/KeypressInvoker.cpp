#pragma once
#include "stdafx.h"
#include "KeypressInvoker.h"
#include "Engine.h"

/// @brief
/// Register keybinds in the invoker for the first time, 
/// throws exception when trying to register multiple commands under the same binding
/// @param code
/// The keycode for the command in the map
/// @param command
/// A shared pointer to the command which needs to be registered
void KeypressInvoker::registerCommand(KeyCode code, ICommand* command) {
	if (isRegistered(*command)) 
		throw exception("keycode already registered, cannot override");
	commands.insert(make_pair(code, command));
};

/// @brief
/// Update the keycode that is set to this command
/// @param code
/// The new keycode for the command in the map
/// @param command
/// A shared pointer to the command which needs to be updated
void KeypressInvoker::updateCommand(KeyCode code, ICommand* command) {

	if (! isRegistered(*command))
		throw exception("trying to update an unregistered command");

	// check if the keycode for this new command has been registered
	// if so, swap them, else, register the new key for this command
	if (isRegistered(code)) {
		for (pair<KeyCode, ICommand*> registeredCommand : commands)
		{

			if (registeredCommand.second->getIdentifier() == command->getIdentifier())
			{
				swap(registeredCommand.second, command);
				return;
			}
		}
	}
	else
		commands[code] = command;
}

/// @brief
/// Delete a command registered to the given keycode
void KeypressInvoker::deleteCommandThatBelongsTo(const KeyCode& keycode) {
	if (isRegistered(keycode))
	{
		commands.erase(keycode);
	}
}

/// @brief
/// Handle commands placed in the command queue each frame
void KeypressInvoker::executeCommandQueue(EventDispatcher& dispatcher)
{
	for (size_t i = 0; i < executionQueue.size(); i++)
	{
		KeyCode& key = executionQueue.front();
		commands[key]->execute(dispatcher);

		executionQueue.pop();
	}
};

/// @brief
/// Attempts to execute a command for a given keycode,
/// fails silently when no bind is registered to prevent unwanted exceptions
/// @param code
/// Keycode for the to execute command
void KeypressInvoker::enqueueCommand(const KeyCode& code) {
	if (isRegistered(code))
		executionQueue.push(code);
};


bool KeypressInvoker::isRegistered(const ICommand& command) {
	auto it = commands.begin();
	while (it != commands.end())
	{
		if (it->second == &command) return true;
		++it;
	}
	return false;
}

bool KeypressInvoker::isRegistered(const KeyCode& keyCode) {
	return commands.find(keyCode) != commands.end();
}