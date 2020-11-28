#include "pch.h"
#include "Commands/Factory/CommandFactory.h"
#include "CommandBuilder.h"
#include <Commands\Factory\CreatorImpl.h>

#include "Commands/Character_commands/MoveLeftCommand.h"
#include "Commands/Character_commands/MoveRightcommand.h"
#include "Commands/Character_commands/JumpCommand.h"
#include <Commands\Character_commands\StopMovementCommand.h>

// TODO read keybinds from file
void CommandBuilder::create()
{
	keypressInvoker->registerCommands(KeyCode::KEY_A, commandFactory->create("moveRightCommand", player));
	keypressInvoker->registerCommands(KeyCode::KEY_D, commandFactory->create("moveLeftCommand",  player));
	keypressInvoker->registerCommands(KeyCode::KEY_SPACE, commandFactory->create("jumpCommand",  player));
}

void CommandBuilder::initFactory()
{
	auto* jumpCommand = new CreatorImpl<JumpCommand, CommandFactory>("jumpCommand");
	auto* moveLeftCommand = new CreatorImpl<MoveLeftCommand, CommandFactory>("moveLeftCommand");
	auto* moveRightCommand = new CreatorImpl<MoveRightCommand, CommandFactory>("moveRightCommand");
	auto* stopMovementCommand = new CreatorImpl<StopMovementCommand, CommandFactory>("stopMovementCommand");

	jumpCommand->registerClass(commandFactory);
	moveLeftCommand->registerClass(commandFactory);
	moveRightCommand->registerClass(commandFactory);
	stopMovementCommand->registerClass(commandFactory);
}
