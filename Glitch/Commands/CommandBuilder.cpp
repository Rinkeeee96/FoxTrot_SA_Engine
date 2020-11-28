#include "pch.h"
#include "Commands/KeypressInvoker.h"
#include "Commands/Factory/CommandCreator.h"
#include "Commands/Factory/CommandFactory.h"
#include "CommandBuilder.h"


#include "Commands/Character_commands/MoveLeftCommand.h"
#include "Commands/Character_commands/MoveRightcommand.h"
#include "Commands/Character_commands/JumpCommand.h"
#include <Commands\Character_commands\StopMovementCommand.h>

// TODO read keybinds from file
void CommandBuilder::linkCommandsToPlayer(ICharacter& player)
{
	keypressInvoker->registerCommands(KeyCode::KEY_A, commandFactory->create("moveRightCommand", player));
	keypressInvoker->registerCommands(KeyCode::KEY_D, commandFactory->create("moveLeftCommand",  player));
	keypressInvoker->registerCommands(KeyCode::KEY_SPACE, commandFactory->create("jumpCommand",  player));
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
