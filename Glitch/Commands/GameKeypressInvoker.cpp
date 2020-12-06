#include "pch.h"
#include "GameKeypressInvoker.h"

#include "Game/characters/Player/Player.h"
unordered_map<KeyCode, string>& GameKeypressInvoker::getPlayerCommands() { return this->playerCommands; }

void GameKeypressInvoker::updateCollection(unordered_map<KeyCode, string>& commandList, KeyCode code, ICommand* command) {
	for (auto commandIt = commandList.begin(); commandIt->second != command->getIdentifier(); ++commandIt)
	{
		// zoek het commando op in de lijst
		if ((commandIt->second == command->getIdentifier()))
		{
			// sla het oude commando op
			string oldCommand = commandList[code];
			// zet het nieuwe commando op zijn plaats
			commandList[code] = command->getIdentifier();
			// zet het oude command op de nu oude plek
			commandIt->second = oldCommand;

			// update het commando in de baseclass
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