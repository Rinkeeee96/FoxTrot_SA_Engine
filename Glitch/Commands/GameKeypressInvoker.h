#pragma once
#include "Commands/ICharacterCommand.h"
#include "Engine/Input/Commands/KeypressInvoker.h"
class Player;
class GameKeypressInvoker : public KeypressInvoker
{
public:
	GameKeypressInvoker(
		unordered_map<KeyCode, string> _playerCommands,
		unordered_map<KeyCode, string> _globalCommands) : 
		playerCommands {_playerCommands}, 
		globalCommands{ _globalCommands } 
	{}

	unordered_map<KeyCode, string>& getPlayerCommands();
	void updatePlayerCommand(KeyCode code, ICharacterCommand* command);
	void destroyPlayercommands();

	unordered_map<KeyCode, string>& getGlobalCommands();
	void updateGlobalCommand(KeyCode code, ICommand* command);
	void destroyGlobalCommands();

private:
	unordered_map<KeyCode, string> playerCommands;
	unordered_map<KeyCode, string> globalCommands;
	void updateCollection(unordered_map<KeyCode, string>& commandList, KeyCode code, ICommand* command);
};