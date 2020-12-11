#pragma once
#include "Game/Commands/Builder/ICommandBuilder.h"
class GameKeypressInvoker;
class Player;

class CharacterCommandFactory;
class UICommandFactory;
class UICommand;

class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder() {};
	GameKeypressInvoker* readBindingsAndCreateInvoker() override;

	// Inherited via ICommandBuilder
	void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) override;
	void linkCommandToToggle(GameKeypressInvoker* invoker, int layerId, UICommand* command);

private:
	shared_ptr<CharacterCommandFactory> characterCommandFactory;
	shared_ptr<UICommandFactory> uiCommandFactory;

	// Inherited via ICommandBuilder
	void initCharacterFactory();
	void initGlobalFactory();
};