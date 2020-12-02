#include "pch.h"
#include "CommandBuilder.h"
#include "Commands/Factory/CommandCreator.h"
#include "Commands/Factory/CommandFactory.h"

#include "Game/Characters/Player/Player.h"

#include "Commands/Character_commands/MoveLeftCommand.h"
#include "Commands/Character_commands/MoveRightcommand.h"
#include "Commands/Character_commands/JumpCommand.h"
#include "Commands/Character_commands/StopMovementCommand.h"

CommandBuilder::CommandBuilder()
{
	keypressInvoker = new GameKeypressInvoker();
	commandFactory = std::shared_ptr<CommandFactory>(new CommandFactory());
	initFactory();
}

// TODO read keybinds from file
void CommandBuilder::buildCommandList()
{
	keypressInvoker->registerPlayerCommand(KeyCode::KEY_A, commandFactory->createCharacterCommand("moveLeftCommand"));
	keypressInvoker->registerPlayerCommand(KeyCode::KEY_D, commandFactory->createCharacterCommand("moveRightCommand"));
	keypressInvoker->registerPlayerCommand(KeyCode::KEY_SPACE, commandFactory->createCharacterCommand("jumpCommand"));
};

GameKeypressInvoker* CommandBuilder::getKeypressInvoker() {
	return keypressInvoker;
}


void CommandBuilder::initFactory()
{
	auto* jumpCommand = new CommandCreator<JumpCommand>("jumpCommand");
	auto* moveLeftCommand = new CommandCreator<MoveLeftCommand>("moveLeftCommand");
	auto* moveRightCommand = new CommandCreator<MoveRightCommand>("moveRightCommand");
	auto* stopMovementCommand = new CommandCreator<StopMovementCommand>("stopMovementCommand");

	jumpCommand->registerClass(commandFactory);
	moveLeftCommand->registerClass(commandFactory);
	moveRightCommand->registerClass(commandFactory);
	stopMovementCommand->registerClass(commandFactory);
} 
