#include "pch.h"
#include "GameKeypressInvoker.h"

#include "Game/characters/Player/Player.h"
unordered_map<KeyCode, string>& GameKeypressInvoker::getPlayerCommands() { return this->playerCommands; }
unordered_map<KeyCode, string>& GameKeypressInvoker::getGlobalCommands() { return globalCommands; }

/// @brief
/// update a the playercommands
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updatePlayerCommand(KeyCode code, const string& identifier)
{
	updateKeycodeInCollection(playerCommands, code, identifier);
}

/// @brief
/// update a the global commands
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updateGlobalCommand(KeyCode code, const string& identifier)
{
	updateKeycodeInCollection(globalCommands, code, identifier);
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
/// update a keycode / command binding collection within the gamekeypressinvoker
/// @param commandList the list with commands
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updateKeycodeInCollection(unordered_map<KeyCode, string>& commandList, KeyCode code, const string& identifier) {
	for (auto commandIt = commandList.begin(); commandIt != commandList.end(); ++commandIt)
	{
		if ((commandIt->second == identifier))
		{
			// swap the commands with a custom method instead of the built in 
			// because we cannot use keycodes
			if (! commandList[code].empty())
			{
				string oldCommand = commandList[code];
				commandList[code] = identifier;
				commandIt->second = oldCommand;
			}
			else {
				commandList[code] = identifier;
				commandList.erase(commandIt);
				
			}

			return;
		}
	}

	//KeypressInvoker::updateCommand(code, identifier);
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

	return KeyCode::KEY_UNKNOWN;

	//throw exception("no keycode registered for " + identifier);
}