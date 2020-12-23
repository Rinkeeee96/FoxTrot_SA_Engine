#pragma once
class Player;
class GameKeypressInvoker;
class ICommandBuilder
{
public:
	virtual GameKeypressInvoker* readBindingsAndCreateInvoker() = 0;
	virtual void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) = 0;
	virtual void linkCommandToToggle(GameKeypressInvoker* invoker, int layerId, const string& identifier) = 0;
	virtual void saveKeybindings(GameKeypressInvoker* invoker) = 0;
};