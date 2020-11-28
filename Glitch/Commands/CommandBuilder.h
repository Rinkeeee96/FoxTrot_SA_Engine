#pragma once
#include "ICommandBuilder.h"
class CommandFactory;
class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder() : commandFactory{new CommandFactory() } 
	{
		initFactory();
	};
	~CommandBuilder() {};

private:
	shared_ptr<CommandFactory> commandFactory;
	shared_ptr<KeypressInvoker> keypressInvoker;

	// Inherited via ICommandBuilder
	virtual void linkCommandsToPlayer(ICharacter& player) override;
	virtual void initFactory() override;

};