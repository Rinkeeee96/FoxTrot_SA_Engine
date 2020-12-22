#include "pch.h"
#include "CommandBuilder.h"

#include "Game/Commands/Creator/GlobalCommands/GlobalCommandCreator.h"
#include "Game/Commands/Creator/GlobalCommands/GlobalCommandFactory.h"

#include "Game/Commands/Creator/CharacterCommands/CharacterCommandFactory.h"
#include "Game/Commands/Creator/CharacterCommands/CharacterCommandCreator.h"

#include "Game/Characters/Player/Player.h"

#include "Game/Commands/CharacterCommands/CharacterCommands.h"

#include "Game/Commands/GameKeypressInvoker.h"
#include "Game/Commands/GlobalCommands/ToggleLayerCommand.h"

CommandBuilder::CommandBuilder()
{
	initCharacterFactory();
	initGlobalCommandFactory();
}

/// @brief
/// read the bindings from the given input source, create a new game keypress invoker and
/// register the bindings in pairs
/// @returns
/// GamekeypressInvoker with the bindings that were registered in the config file.
/// When it fails it attempts to go back to the default bindings
GameKeypressInvoker* CommandBuilder::readBindingsAndCreateInvoker() {

	bool parseError = false;
	// binding "out" variables
	unordered_map<KeyCode, string> playerBindings;
	unordered_map<KeyCode, string> globalBindings;

	GameKeypressInvoker* invoker = nullptr;

	ifstream stream;
	try
	{
		stream = fileLoader.readFile(keybindingConfigFilepath);
		stream >> json;
		stream.close();

		bool validConfigFile = fileLoader.validateDocument(keybindingConfigFilepath, "Assets/Config/keybinding-validation-schema.json");
		if (validConfigFile) {
			parseKeybindingsToMap(playerBindings, globalBindings);
			invoker = new GameKeypressInvoker(playerBindings, globalBindings);
		}
		else {
			throw exception("CommandBuilder: Something went wrong validating file, make sure the file is correct");
		}
	}
	catch (const std::exception& e)
	{
		cout <<"Error while parsing keybindings \n" << e.what() << ", resetting..." << endl;
		this->createDefaultbindings(playerBindings, globalBindings);
		invoker = new GameKeypressInvoker(playerBindings, globalBindings);
		this->saveKeybindings(invoker);
	}
	return invoker;
}

/// @brief
/// Wrapper method for parsing the generic keybinding list on the lowest level since the structure is equal
/// places them directly into the given map
/// @param commandListRef
/// the list to place the parsed commands into
/// @param subCollection
/// the subcollection containing the bindings on the lowest level of the json structure
void CommandBuilder::parseCommandList(nlohmann::json& subCollection, unordered_map<KeyCode, string>& commandListRef)
{
	for (nlohmann::json::iterator it = subCollection.begin(); it != subCollection.end(); ++it) {
		string identifier = it.key();
		KeyCode keycode = it.value();

		commandListRef[keycode] = identifier;
	}
}

/// @brief
/// wrapper method for parsing the bindings for each list since the player is structured as an array
/// @param playerBindings
/// @param globalBindings
void CommandBuilder::parseKeybindingsToMap(unordered_map<KeyCode, string>& playerBindings, unordered_map<KeyCode, string>& globalBindings)
{
	// TODO ensure multiplayer bindings are supported (put this here for future reference)
	for (auto& player : json["player"])
		parseCommandList(player, playerBindings);
	
	parseCommandList(json["global"], globalBindings);
}

/// @brief
/// Converts the given keybinding collection to a json in key value pairs.
void CommandBuilder::parseKeybindingsToJson(nlohmann::json& json, unordered_map<KeyCode, string>& collection)
{
	for (pair<KeyCode, string> bindingPair : collection)
	{
		KeyCode& keycode = bindingPair.first;
		const string& identifier = bindingPair.second;
		int parsedKeycode = static_cast<int>(keycode);
		json[identifier] = parsedKeycode;
	}
}

/// @brief
/// Saves the keybindings that are currently stored in the game keypress invoker, overwrites the last file.
/// @param invoker
/// the invoker which contains the bindings to save
void CommandBuilder::saveKeybindings(GameKeypressInvoker* invoker)
{
	nlohmann::json outputJson;

	nlohmann::json playerBindings;
	nlohmann::json globalBindings;
	parseKeybindingsToJson(playerBindings, invoker->getPlayerCommands());
	parseKeybindingsToJson(globalBindings, invoker->getGlobalCommands());

	std::ofstream file(keybindingConfigFilepath);
	outputJson["global"] = globalBindings;
	outputJson["player"] = playerBindings;

	// update the local json
	json = outputJson;
	// store the configuration in the output file
	file << json;
}


/// @brief
/// create the default keybindings, this method is generally called when bindings cannot be loaded
/// to prevent the user from being locked out
/// @param playerBindings
/// @param globalBindings
void CommandBuilder::createDefaultbindings(unordered_map<KeyCode, string>& playerBindings, unordered_map<KeyCode, string>& globalBindings)
{
	playerBindings = {
		{ KeyCode::KEY_A, "moveLeft" },
		{ KeyCode::KEY_D, "moveRight" },
		{ KeyCode::KEY_G, "godmode" },
		{ KeyCode::KEY_SPACE, "jump" }
	};

	globalBindings = {
		{ KeyCode::KEY_P, "pause" },
		{ KeyCode::KEY_I, "inventory" }
	};
}

/// @brief
/// build the player commands
void CommandBuilder::buildPlayerCommands(Player& player, GameKeypressInvoker* invoker)
{
	// first = keycode, second = identifier
	for (auto pair = invoker->getPlayerCommands().begin(); pair != invoker->getPlayerCommands().end(); ++pair)
	{
		try
		{
			invoker->registerCommand(
				pair->first, 
				characterCommandFactory->createCharacterCommand(pair->second, player)
			);
		}
		catch (const exception& e)
		{
			// TODO throw up further and create a popup for missparsed bindings
			if (DEBUG_COMMAND_BUILDER) cout << e.what();
			++pair;
		}

	}
	player.registerKeypressInvoker(invoker);
}

/// @brief
/// Finds and links layers to a given identifier, bubbles exception thrown in invoker
/// @param invoker the pointer to the currently active game invoker
/// @param layerId the identifier for the given layer for the toggleCommand
/// @param identifier the identifier for the command
void CommandBuilder::linkCommandToToggle(GameKeypressInvoker* invoker, int layerId, const string& identifier)
{
	invoker->registerCommand(
		invoker->getKeycodeFromIdentifier(identifier),
		globalCommandFactory->createCommand(identifier, layerId)
	);
}

/// @brief
/// initialise the character command factory and register it's commands
void CommandBuilder::initCharacterFactory()
{
	characterCommandFactory = std::shared_ptr<CharacterCommandFactory>(new CharacterCommandFactory());

	auto* jumpCommand = new CharacterCommandCreator<JumpCommand>("jump");
	auto* moveLeftCommand = new CharacterCommandCreator<MoveLeftCommand>("moveLeft");
	auto* moveRightCommand = new CharacterCommandCreator<MoveRightCommand>("moveRight");
	auto* godmodeCommand = new CharacterCommandCreator<GodmodeCommand>("godmode");

	godmodeCommand->registerClass(characterCommandFactory);
	jumpCommand->registerClass(characterCommandFactory);
	moveLeftCommand->registerClass(characterCommandFactory);
	moveRightCommand->registerClass(characterCommandFactory);
}

/// @brief
/// initialise the global command factory and register it's commands
void CommandBuilder::initGlobalCommandFactory()
{
	globalCommandFactory = std::shared_ptr<GlobalCommandFactory>(new GlobalCommandFactory());
	auto toggleInventoryCommand = new GlobalCommandCreator<ToggleLayerCommand>("inventory");
	auto togglePauseCommand = new GlobalCommandCreator<ToggleLayerCommand>("pause");

	toggleInventoryCommand->registerClass(globalCommandFactory);
	togglePauseCommand->registerClass(globalCommandFactory);
}