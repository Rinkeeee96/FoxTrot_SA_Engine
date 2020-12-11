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
	void linkCommandToToggle(GameKeypressInvoker* invoker, int layerId, const string& identifier) override;
private:
	shared_ptr<CharacterCommandFactory> characterCommandFactory;
	shared_ptr<UICommandFactory> uiCommandFactory;

	void initCharacterFactory();
	void initUICommandFactory();
};