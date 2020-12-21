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
GameKeypressInvoker* CommandBuilder::readBindingsAndCreateInvoker() {

	bool parseError = false;

	unordered_map<KeyCode, string> playerBindings;
	unordered_map<KeyCode, string> globalBindings;
	pair<unordered_map<KeyCode, string>, unordered_map<KeyCode, string>> pair;

	GameKeypressInvoker* invoker = nullptr;

	ifstream stream;
	try
	{
		stream = fileLoader.readFile(keybindingConfigFilepath);
		stream >> json;
		pair = parseKeybindings();

		playerBindings = pair.first;
		globalBindings = pair.second;

		invoker = new GameKeypressInvoker(playerBindings, globalBindings);
	}
	catch (const std::exception&)
	{
		cout << "Keybindings file not found, resetting..." << endl;
		pair = this->createDefaultbindings();
		playerBindings = pair.first;
		globalBindings = pair.second;

		invoker = new GameKeypressInvoker(playerBindings, globalBindings);

		this->saveKeybindings(invoker);
	}
	return invoker;
}

void CommandBuilder::parseCommandList(nlohmann::json& subCollection, unordered_map<KeyCode, string>& commandListRef)
{
	for (nlohmann::json::iterator it = subCollection.begin(); it != subCollection.end(); ++it) {
		string identifier = it.key();
		KeyCode keycode = it.value();

		commandListRef[keycode] = identifier;
	}
}

pair<unordered_map<KeyCode, string>, unordered_map<KeyCode, string>> CommandBuilder::parseKeybindings()
{
	unordered_map<KeyCode, string> playerBindings;
	//for (auto& player : json["player"])
		//playerBindings.emplace(parseCommandList(player));
	
	unordered_map<KeyCode, string> globalBindings = parseCommandList(json["global"]);

	return make_pair(playerBindings, globalBindings);
}

pair<unordered_map<KeyCode, string>, unordered_map<KeyCode, string>> CommandBuilder::createDefaultbindings()
{
	unordered_map<KeyCode, string> playerBindings = {
		{ KeyCode::KEY_A, "moveLeft" },
		{ KeyCode::KEY_D, "moveRight" },
		{ KeyCode::KEY_G, "godmode" },
		{ KeyCode::KEY_SPACE, "jump" }
	};

	unordered_map<KeyCode, string> globalBindings = {
		{ KeyCode::KEY_P, "pause" },
		{ KeyCode::KEY_I, "inventory" }
	};

	return make_pair(playerBindings, globalBindings);
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
void CommandBuilder::saveKeybindings(GameKeypressInvoker* invoker)
{
	nlohmann::json outputJson;

	nlohmann::json playerBindings;
	nlohmann::json globalBindings;
	parseCollectionToJson(playerBindings, invoker->getPlayerCommands());
	parseCollectionToJson(globalBindings, invoker->getGlobalCommands());

	std::ofstream file(keybindingConfigFilepath);
	outputJson["global"] = globalBindings;
	outputJson["player"] = playerBindings;

	// update the local json
	json = outputJson;
	// store the configuration in the output file
	file << json;
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

void CommandBuilder::parseCollectionToJson(nlohmann::json& json, unordered_map<KeyCode, string>& collection)
{
	for (pair<KeyCode, string> bindingPair : collection)
	{
		KeyCode& keycode = bindingPair.first;
		const string& identifier = bindingPair.second;
		int parsedKeycode = static_cast<int>(keycode);
		json[identifier] = parsedKeycode;
	}
}
