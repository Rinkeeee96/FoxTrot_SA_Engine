#pragma once
#include "Commands/Builder/ICommandBuilder.h"
class GameKeypressInvoker;
class Player;
class CharacterCommandFactory;

class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder() {};
	GameKeypressInvoker* readBindingsAndCreateInvoker() override;
	void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) override;
private:
	shared_ptr<CharacterCommandFactory> characterCommandFactory;

	// Inherited via ICommandBuilder
	virtual void initFactory() override;
};