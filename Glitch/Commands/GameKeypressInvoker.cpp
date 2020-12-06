#include "pch.h"
#include "GameKeypressInvoker.h"

#include "Game/characters/Player/Player.h"
unordered_map<KeyCode, string>& GameKeypressInvoker::getPlayerCommands() { return this->playerCommands; }

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

			KeypressInvoker::updateCommand(code, command);
			return;
		}
	}
}

void GameKeypressInvoker::updatePlayerCommand(KeyCode code, ICharacterCommand* command)
{
	updateCollection(playerCommands, code, command);
}
unordered_map<KeyCode, string>& GameKeypressInvoker::getGlobalCommands() { return globalCommands; }

void GameKeypressInvoker::updateGlobalCommand(KeyCode code, ICommand* command)
{
	updateCollection(globalCommands, code, command);
}

// TODO implement
void GameKeypressInvoker::destroyGlobalCommands()
{
	for (auto pair : globalCommands)
	{
		KeyCode keycode = pair.first;
		deleteCommandThatBelongsTo(keycode);
	}
}

void GameKeypressInvoker::destroyPlayercommands()
{
	for (auto pair : playerCommands)
	{
		KeyCode keycode = pair.first;
		deleteCommandThatBelongsTo(keycode);
	}
}