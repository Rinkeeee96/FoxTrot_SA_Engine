#pragma once
#include "ICommandBuilder.h"
#include <Commands\KeypressInvoker.h>
class CommandFactory;
class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder(ICharacter* _player) : 
		player{ _player },
		commandFactory{new CommandFactory() } 
	{
		initFactory();
	};
	~CommandBuilder() {};

private:
	ICharacter* player;

	shared_ptr<CommandFactory> commandFactory;
	shared_ptr<KeypressInvoker> keypressInvoker;

	// Inherited via ICommandBuilder
	virtual void create() override;
	virtual void initFactory() override;

};