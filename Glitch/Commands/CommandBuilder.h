#pragma once
#include "Commands/ICommandBuilder.h"
class KeypressInvoker;
class Player;
class CommandFactory;

class CommandBuilder : public ICommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder() {};
	shared_ptr<KeypressInvoker> getKeypressInvoker() { return keypressInvoker; }
	void linkCommandsToPlayer(Player& player) override;

private:
	shared_ptr<CommandFactory> commandFactory;
	shared_ptr<KeypressInvoker> keypressInvoker;

	// Inherited via ICommandBuilder
	virtual void initFactory() override;
};