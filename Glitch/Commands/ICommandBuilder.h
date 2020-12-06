#pragma once
class Player;
class GameKeypressInvoker;
class ICommandBuilder
{
public:
	virtual void initFactory() = 0;
	virtual GameKeypressInvoker* readBindingsAndCreateInvoker() = 0;
	virtual void buildPlayerCommands(Player& player, GameKeypressInvoker* invoker) = 0;
};