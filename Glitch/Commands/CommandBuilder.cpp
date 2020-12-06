#include "pch.h"
#include "CommandBuilder.h"
#include "Commands/Factory/CommandCreator.h"
#include "Commands/Factory/CommandFactory.h"

#include "Game/Characters/Player/Player.h"

#include "Commands/Character_commands/MoveLeftCommand.h"
#include "Commands/Character_commands/MoveRightcommand.h"
#include "Commands/Character_commands/JumpCommand.h"
#include "Commands/Character_commands/StopMovementCommand.h"

#include "Commands/exceptions/unknownCommandException.h"

#include "Commands/GameKeypressInvoker.h"

CommandBuilder::CommandBuilder()
{
	initFactory();
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

void CommandBuilder::initFactory()
{
	commandFactory = std::shared_ptr<CommandFactory>(new CommandFactory());

	auto* jumpCommand = new CommandCreator<JumpCommand>("jump");
	auto* moveLeftCommand = new CommandCreator<MoveLeftCommand>("moveLeft");
	auto* moveRightCommand = new CommandCreator<MoveRightCommand>("moveRight");
	//auto* stopMovementCommand = new CommandCreator<StopMovementCommand>("stopMovement");

	jumpCommand->registerClass(commandFactory);
	moveLeftCommand->registerClass(commandFactory);
	moveRightCommand->registerClass(commandFactory);
	//stopMovementCommand->registerClass(commandFactory);
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
				commandFactory->createCharacterCommand(pair->second, player)
			);
		}
		catch (const unknownCommandException& e)
		{
			// TODO throw up further and create a popup for missparsed bindings
			if (DEBUG_COMMAND_BUILDER) cout << e.what();
			++pair;
		}

		player.registerKeypressInvoker(invoker);
	}
};