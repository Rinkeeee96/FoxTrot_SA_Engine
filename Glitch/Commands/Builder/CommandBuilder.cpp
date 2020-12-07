#include "pch.h"
#include "CommandBuilder.h"

#include "Commands/Creator/GlobalCommands/CommandCreator.h"
#include "Commands/Creator/GlobalCommands/CommandFactory.h"

#include "Commands/Creator/CharacterCommands/CharacterCommandFactory.h"
#include "Commands/Creator/CharacterCommands/CharacterCommandCreator.h"

#include "Game/Characters/Player/Player.h"

#include "Commands/CharacterCommands/MoveLeftCommand.h"
#include "Commands/CharacterCommands/MoveRightcommand.h"
#include "Commands/CharacterCommands/JumpCommand.h"
#include "Commands/CharacterCommands/StopMovementCommand.h"

#include "Commands/GlobalCommands/PauseCommand.h"

#include "Commands/exceptions/unknownCommandException.h"

#include "Commands/GameKeypressInvoker.h"

CommandBuilder::CommandBuilder()
{
	initCharacterFactory();
	//initGlobalFactory();
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
GameKeypressInvoker* CommandBuilder::readBindingsAndCreateInvoker() {
	// bindings now belong "hardcoded" to the player
	unordered_map<KeyCode, string> playerBindings = {
		{ KeyCode::KEY_A, "moveLeft" },
		{ KeyCode::KEY_D, "moveRight" },
		{ KeyCode::KEY_SPACE, "jump" }
	};

	unordered_map<KeyCode, string> globalBindings = {
		{ KeyCode::KEY_P, "pause" }
	};

	return new GameKeypressInvoker(playerBindings, globalBindings);
}

void CommandBuilder::initCharacterFactory()
{
	characterCommandFactory = std::shared_ptr<CharacterCommandFactory>(new CharacterCommandFactory());

	auto* jumpCommand = new CharacterCommandCreator<JumpCommand>("jump");
	auto* moveLeftCommand = new CharacterCommandCreator<MoveLeftCommand>("moveLeft");
	auto* moveRightCommand = new CharacterCommandCreator<MoveRightCommand>("moveRight");

	jumpCommand->registerClass(characterCommandFactory);
	moveLeftCommand->registerClass(characterCommandFactory);
	moveRightCommand->registerClass(characterCommandFactory);
}

void CommandBuilder::initGlobalFactory()
{
	generalCommandFactory = std::shared_ptr<CommandFactory>();
	auto* pauseCommand = new CommandCreator<PauseCommand>("pause");

	//pauseCommand->registerClass(generalCommandFactory);
}


void CommandBuilder::buildGlobalCommands(GameKeypressInvoker* invoker)
{
	// first = keycode, second = identifier
	for (auto pair = invoker->getGlobalCommands().begin(); pair != invoker->getGlobalCommands().end(); ++pair)
	{
		try
		{
			invoker->registerCommand(
				pair->first,
				generalCommandFactory->create(pair->second)
			);
		}
		catch (const unknownCommandException& e)
		{
			// TODO throw up further and create a popup for missparsed bindings
			if (DEBUG_COMMAND_BUILDER) cout << e.what();
			++pair;
		}
	}
}

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
		catch (const unknownCommandException& e)
		{
			// TODO throw up further and create a popup for missparsed bindings
			if (DEBUG_COMMAND_BUILDER) cout << e.what();
			++pair;
		}

	}
	player.registerKeypressInvoker(invoker);
};