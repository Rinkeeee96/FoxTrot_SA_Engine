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

// TODO read keybinds from file
/*
global: {
	KEY_P: "pause",
	.....
},
player : {
	{
		KEY_A : "walkLeft",
		KEY_D : "walkRight"
		....
	},
	{
		....
	}
}
*/
/// @brief
/// read the bindings from the given input source, create a new game keypress invoker and
/// register the bindings in pairs
GameKeypressInvoker* CommandBuilder::readBindingsAndCreateInvoker() {
	// bindings now belong "hardcoded" to the player
	unordered_map<KeyCode, string> playerBindings = {
		{ KeyCode::KEY_A, "moveLeft"},
		{ KeyCode::KEY_D, "moveRight"},
		{ KeyCode::KEY_G, "godmode"},
		{ KeyCode::KEY_SPACE, "jump"}
	};

	unordered_map<KeyCode, string> globalBindings = {
		{ KeyCode::KEY_P, "pause" },
		{ KeyCode::KEY_H, "help" },
		{ KeyCode::KEY_I, "inventory" }
	};

	return new GameKeypressInvoker(playerBindings, globalBindings);
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
	auto toggleHelpCommand = new GlobalCommandCreator<ToggleLayerCommand>("help");

	toggleInventoryCommand->registerClass(globalCommandFactory);
	togglePauseCommand->registerClass(globalCommandFactory);
	toggleHelpCommand->registerClass(globalCommandFactory);
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
};