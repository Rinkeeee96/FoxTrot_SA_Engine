#include "pch.h"
#include "GameKeypressInvoker.h"

#include "Game/characters/Player/Player.h"
unordered_map<KeyCode, string>& GameKeypressInvoker::getPlayerCommands() { return this->playerCommands; }
unordered_map<KeyCode, string>& GameKeypressInvoker::getGlobalCommands() { return globalCommands; }

/// @brief
/// update a the playercommands
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updatePlayerCommand(KeyCode code, ICommand* command)
{
	updateCollection(playerCommands, code, command);
}

/// @brief
/// update a the global commands
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updateGlobalCommand(KeyCode code, ICommand* command)
{
	updateCollection(globalCommands, code, command);
}

/// @brief
/// Loops over all global commands and calls destruction method in base invoker
void GameKeypressInvoker::destroyGlobalCommands()
{
	destroyCollection(globalCommands);
}
/// @brief
/// Loops over all player commands and calls destruction method in base invoker
void GameKeypressInvoker::destroyPlayercommands()
{
	destroyCollection(playerCommands);
}

/// @brief
/// Loops over the given commands collection and calls destruction method in base invoker
void GameKeypressInvoker::destroyCollection(unordered_map<KeyCode, string>& commandList)
{
	for (auto pair : commandList)
	{
		KeyCode keycode = pair.first;
		deleteCommandThatBelongsTo(keycode);
	}
}

/// @brief
/// update a collection within the gamekeypressinvoker
/// @param commandList the list with commands
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updateCollection(unordered_map<KeyCode, string>& commandList, KeyCode code, ICommand* command) {
	for (auto commandIt = commandList.begin(); commandIt->second != command->getIdentifier(); ++commandIt)
	{
		if ((commandIt->second == command->getIdentifier()))
		{
			// swap the commands with a custom method instead of the built in 
			// because we cannot use keycodes
			string oldCommand = commandList[code];
			commandList[code] = command->getIdentifier();
			commandIt->second = oldCommand;

			continue;
		}
	}

	KeypressInvoker::updateCommand(code, command);
}

/// @brief
/// Finds and returns the keycode with a given identifier
/// throws exception if it does not exist
/// @param identifier the given identifier string for the command
const KeyCode& GameKeypressInvoker::getKeycodeFromIdentifier(const string& identifier)
{
	for (auto pair : globalCommands)
	{
		if (identifier == pair.second)
			return pair.first;
	}

	for (auto pair : playerCommands)
	{
		if (identifier == pair.second)
			return pair.first;
	}

	throw exception("no keycode registered for " + identifier);
}