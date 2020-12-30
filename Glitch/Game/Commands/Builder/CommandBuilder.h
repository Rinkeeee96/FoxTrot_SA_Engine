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
	void buildGlobalCommands(GameKeypressInvoker* invoker) override;

	void saveKeybindings(GameKeypressInvoker* invoker);

private:
	shared_ptr<CharacterCommandFactory> characterCommandFactory;
	shared_ptr<GlobalCommandFactory> globalCommandFactory;

	const string keybindingConfigFilepath = "Assets/config/keybindings.json";
	nlohmann::json json;
	FileLoader fileLoader;

	void initCharacterFactory();
	void initGlobalCommandFactory();

	void parseKeybindingsToJson(nlohmann::json& json, unordered_map<KeyCode, string>& collection);

	void parseCommandList(nlohmann::json& subCollection, unordered_map<KeyCode, string>& commandListRef);

	void parseKeybindingsToMap(unordered_map<KeyCode, string>& playerBindings, unordered_map<KeyCode, string>& globalBindings);
	void createDefaultbindings(unordered_map<KeyCode, string>& playerBindings, unordered_map<KeyCode, string>& globalBindings);
};