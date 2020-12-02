#include "GameKeypressInvoker.h"

#include "Game/characters/Player/Player.h"
void GameKeypressInvoker::registerPlayerCommand(KeyCode code, unique_ptr<ICharacterCommand> command) {
	KeypressInvoker::registerCommands(code, move(command));
	playerCommands[code] = command;
}

unordered_map<KeyCode, reference_wrapper<unique_ptr<ICharacterCommand>>>& GameKeypressInvoker::getPlayerCommands() { return this->playerCommands; }

void GameKeypressInvoker::registerGlobalCommand(KeyCode code, unique_ptr<ICommand> command) {
	KeypressInvoker::registerCommands(code, move(command));
	globalCommands[code] = command;
}

void GameKeypressInvoker::linkCommandsToPlayer(Player& player)
{
	ICharacter& character = (ICharacter&)player;
	// TODO unknown ICharacterCommand in de lambda????
	for_each(
		playerCommands.begin(),
		playerCommands.end(),
		[&character](ICharacterCommand& command) {
			command.registerCharacter(&character);
		}
	);
	player.registerKeypressInvoker(this);
}

/// @brief
/// Update the keycode that is set to this command, unbinds the previously registerd command if present
/// @param code
/// The new keycode for the command in the map
/// @param command
/// A shared pointer to the command which needs to be updated
void GameKeypressInvoker::updateCommand(KeyCode code, unique_ptr<ICommand> command) {
	if (isRegistered(command))
	{
		playerCommands.erase(code);
		globalCommands.erase(code);
	}

	KeypressInvoker::updateCommand(code, move(command));
};