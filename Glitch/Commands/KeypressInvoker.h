#pragma once
#include "pch.h"
#include "ICharacterCommand.h"
class KeypressInvoker
{
public:
	KeypressInvoker();
	~KeypressInvoker();
	/// @brief
	/// Register keybinds in the invoker for the first time, 
	/// throws exception when trying to register multiple commands under the same binding
	/// @param code
	/// The keycode for the command in the map
	/// @param command
	/// A shared pointer to the command which needs to be registered
	void registerCommands(KeyCode code, shared_ptr<ICommand> command) {
		if (isRegistered(command)) throw exception("keycode already registered, cannot override");

		playerCommands[code] = command;
	};
	/// @brief
	/// Update the keycode that is set to this command, unbinds the previously registerd command if present
	/// @param code
	/// The new keycode for the command in the map
	/// @param command
	/// A shared pointer to the command which needs to be updated
	void updateCommand(KeyCode code, shared_ptr<ICommand> command) {
		// unbind existing command if it has a key bound to it, if so, unbind it
		if (isRegistered(command))
		{
			unboundCommands.push_back(command);
			playerCommands.erase(code);
		}
		// set the command
		playerCommands[code] = command;
	};
	/// @brief
	/// Attempts to execute a command for a given keycode,
	/// fails silently when no bind is registered to prevent unwanted exceptions
	/// @param code
	/// Keycode for the to execute command
	void executeCommand(KeyCode code) {
		if (isRegistered(code)) {
			playerCommands[code]->execute();
		}
	};

private:
	// TODO transfer ownership to command invoker from builder via unique_ptr, I don't intend to keep the builder alive once the initial keybinds have been loaded
	unordered_map<KeyCode, shared_ptr<ICommand>> playerCommands;
	vector<shared_ptr<ICommand>> unboundCommands;

	bool isRegistered(shared_ptr<ICommand> command) {
		auto it = playerCommands.begin();
		while (it != playerCommands.end())
		{
			if (it->second == command)
			{
				return true;
			}
		}
		return false;
	}

	bool isRegistered(const KeyCode& keyCode) {
		return playerCommands.find(keyCode) != playerCommands.end();
	}
};

KeypressInvoker::KeypressInvoker()
{
}

KeypressInvoker::~KeypressInvoker()
{
}