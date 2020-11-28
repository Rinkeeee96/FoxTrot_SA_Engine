#pragma once
class ICommand;

class ICommandBuilder
{
public:
	ICommandBuilder() {};
	virtual ~ICommandBuilder() = 0;

	shared_ptr<unordered_map<KeyCode, ICommand>> getPlayerCommands() { return playerCommands; }
	shared_ptr<unordered_map<KeyCode, ICommand>> getGlobalCommands() { return globalCommands; }

	virtual void create() = 0;
	virtual void initFactory() = 0;

private:
	shared_ptr<unordered_map<KeyCode, ICommand>> playerCommands;
	shared_ptr<unordered_map<KeyCode, ICommand>> globalCommands;
};

ICommandBuilder::ICommandBuilder()
{
}

ICommandBuilder::~ICommandBuilder()
{
}