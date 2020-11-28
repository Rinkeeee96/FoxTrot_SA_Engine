#pragma once
class ICommand;
class ICharacter;

class ICommandBuilder
{
public:
	ICommandBuilder() {};
	virtual ~ICommandBuilder() = 0;

	shared_ptr<unordered_map<KeyCode, ICommand>> getPlayerCommands() { return playerCommands; }
	shared_ptr<unordered_map<KeyCode, ICommand>> getGlobalCommands() { return globalCommands; }

	virtual void linkCommandsToPlayer(ICharacter& character) = 0;
	virtual void initFactory() = 0;

private:
	shared_ptr<unordered_map<KeyCode, ICommand>> playerCommands;
	shared_ptr<unordered_map<KeyCode, ICommand>> globalCommands;
};