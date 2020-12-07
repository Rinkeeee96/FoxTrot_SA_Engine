#pragma once
class Player;
class GameKeypressInvoker;
class ICommandBuilder
{
public:
	virtual GameKeypressInvoker* readBindingsAndCreateInvoker() = 0;
	virtual void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) = 0;
	virtual void buildGlobalCommands(GameKeypressInvoker* invoker) = 0;
};