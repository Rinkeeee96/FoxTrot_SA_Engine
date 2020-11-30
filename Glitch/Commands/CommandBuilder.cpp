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
	keypressInvoker = std::shared_ptr<KeypressInvoker>(new KeypressInvoker());
	commandFactory = std::shared_ptr<CommandFactory>(new CommandFactory());
	initFactory();
};

// TODO read keybinds from file
void CommandBuilder::linkCommandsToPlayer(Player& player)
{
	ICharacter& character = (ICharacter&)player;

	keypressInvoker->registerCommands(KeyCode::KEY_A, commandFactory->create("moveRightCommand", character));
	keypressInvoker->registerCommands(KeyCode::KEY_D, commandFactory->create("moveLeftCommand", character));
	keypressInvoker->registerCommands(KeyCode::KEY_SPACE, commandFactory->create("jumpCommand", character));

	player.registerKeypressInvoker(this->keypressInvoker);
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
