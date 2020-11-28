#pragma once
#include "ICommandBuilder.h"
#include "Commands/Factory/CommandFactory.h"
class KeypressInvoker;
class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder() : commandFactory{new CommandFactory() } 
	{
		initFactory();
	};
	~CommandBuilder() {};
	virtual void linkCommandsToPlayer(ICharacter& player) override;

private:
	shared_ptr<CommandFactory> commandFactory;
	shared_ptr<KeypressInvoker> keypressInvoker;

	// Inherited via ICommandBuilder
	virtual void initFactory() override;
};