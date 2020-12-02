#pragma once
#include "Commands/ICommandBuilder.h"
class GameKeypressInvoker;
class Player;
class CommandFactory;

class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder() {};
	void buildCommandList();
	GameKeypressInvoker* getKeypressInvoker();
private:
	shared_ptr<CommandFactory> commandFactory;

	// Inherited via ICommandBuilder
	virtual void initFactory() override;
};