#pragma once
#include "Game/Commands/ICharacterCommand.h"
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
	void updatePlayerCommand(KeyCode code, const string& identifier);
	void destroyPlayercommands();

	unordered_map<KeyCode, string>& getGlobalCommands();
	void updateGlobalCommand(KeyCode code, const string& identifier);
	const KeyCode& getKeycodeFromIdentifier(const string& identifier);
	void destroyGlobalCommands();

private:
	unordered_map<KeyCode, string> playerCommands;
	unordered_map<KeyCode, string> globalCommands;
	void updateKeycodeInCollection(unordered_map<KeyCode, string>& commandList, unordered_map<KeyCode, string>& controlList, KeyCode code, const string& identifier);
	void destroyCollection(unordered_map<KeyCode, string>& commandList);
};