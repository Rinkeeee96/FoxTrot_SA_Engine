#pragma once
#include "Game/Commands/Builder/ICommandBuilder.h"
class GameKeypressInvoker;
class Player;

class CharacterCommandFactory;
class CommandFactory;

class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder() {};
	GameKeypressInvoker* readBindingsAndCreateInvoker() override;

	// Inherited via ICommandBuilder
	void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) override;
	void buildGlobalCommands(GameKeypressInvoker* invoker) override;
private:
	shared_ptr<CharacterCommandFactory> characterCommandFactory;
	shared_ptr<CommandFactory> generalCommandFactory;

	// Inherited via ICommandBuilder
	void initCharacterFactory();
	void initGlobalFactory();
};