#pragma once
#include "Commands/ICommandBuilder.h"
#include "Commands/Factory/CommandFactory.h"
#include "Game/Characters//Player/Player.h"
class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder()
	{
		keypressInvoker = std::shared_ptr<KeypressInvoker>(new KeypressInvoker());
		commandFactory = std::shared_ptr<CommandFactory>(new CommandFactory());
		initFactory();
	};
	~CommandBuilder() {};
	shared_ptr<KeypressInvoker> getKeypressInvoker() { return keypressInvoker; }
	void linkCommandsToPlayer(Player& player) override;

private:
	shared_ptr<CommandFactory> commandFactory;
	shared_ptr<KeypressInvoker> keypressInvoker;

	// Inherited via ICommandBuilder
	virtual void initFactory() override;
};