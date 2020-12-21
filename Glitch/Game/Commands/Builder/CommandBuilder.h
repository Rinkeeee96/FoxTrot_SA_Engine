#pragma once
#include "Game/Commands/Builder/ICommandBuilder.h"
class GameKeypressInvoker;
class Player;

class CharacterCommandFactory;
class GlobalCommandFactory;
class GlobalCommand;

class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder() {};
	GameKeypressInvoker* readBindingsAndCreateInvoker() override;

	// Inherited via ICommandBuilder
	void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) override;
	void linkCommandToToggle(GameKeypressInvoker* invoker, int layerId, const string& identifier) override;

	void saveKeybindings(GameKeypressInvoker* invoker);
private:
	shared_ptr<CharacterCommandFactory> characterCommandFactory;
	shared_ptr<GlobalCommandFactory> globalCommandFactory;

	const string keybindingConfigFilepath = "Assets/config/keybindings.json";
	nlohmann::json json;
	FileLoader fileLoader;

	void initCharacterFactory();
	void initGlobalCommandFactory();

	void parseCollectionToJson(nlohmann::json& json, unordered_map<KeyCode, string>& collection);

	unordered_map<KeyCode, string> parseCommandList(nlohmann::json& subCollection);

	pair<unordered_map<KeyCode, string>, unordered_map<KeyCode, string>> parseKeybindings();
	pair<unordered_map<KeyCode, string>, unordered_map<KeyCode, string>> createDefaultbindings();
};