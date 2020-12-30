#include "pch.h"
#include "GameKeypressInvoker.h"

#include "Game/characters/Player/Player.h"
unordered_map<KeyCode, string>& GameKeypressInvoker::getPlayerCommands() { return this->playerCommands; }
unordered_map<KeyCode, string>& GameKeypressInvoker::getGlobalCommands() { return globalCommands; }

/// @brief
/// update a playercommand
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updatePlayerCommand(KeyCode code, const string& identifier)
{
	updateKeycodeInCollection(playerCommands, globalCommands, code, identifier);
}

/// @brief
/// update a global command
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updateGlobalCommand(KeyCode code, const string& identifier)
{
	updateKeycodeInCollection(globalCommands, playerCommands, code, identifier);
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
/// @param mapToUpdate the list with commands to update
/// @param controlMap the list to check for occurences of the keybind that sent with the code parameter
/// @param code the new keycode for a command
/// @param command the command to update
void GameKeypressInvoker::updateKeycodeInCollection(unordered_map<KeyCode, string>& mapToUpdate, unordered_map<KeyCode, string>& controlMap, KeyCode code, const string& identifier) {
		
	bool inControlMap = false;
	bool inCommandList = ! mapToUpdate[code].empty();
	for (auto commandIt = controlMap.begin(); commandIt != controlMap.end(); ++commandIt)
	{
		if ((commandIt->first == code))
		{
			inControlMap = true;
		}
	}

	for (auto commandIt = mapToUpdate.begin(); commandIt != mapToUpdate.end(); ++commandIt)
	{
		if ((commandIt->second == identifier))
		{
			// binding is only present in the list to update
			if (inCommandList && ! inControlMap)
			{
				string oldCommand = mapToUpdate[code];
				mapToUpdate[code] = identifier;
				commandIt->second = oldCommand;				
			}
			// binding is present in both the list to update and the control map
			else if (inControlMap)
			{
				mapToUpdate[code] = identifier;
				controlMap.insert(make_pair(commandIt->first, controlMap[code]));

				controlMap.erase(code);
				mapToUpdate.erase(commandIt);
			}
			// new keybinding for command which is not present
			else {
				mapToUpdate[code] = identifier;
				mapToUpdate.erase(commandIt);
			}

			return;
		}
	}
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