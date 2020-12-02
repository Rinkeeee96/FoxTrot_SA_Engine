#pragma once

class ICommand;
class ICharacter;
class ICharacterCommand;
class ICommandCreator;

class CommandFactory
{
public:
	CommandFactory() {};
	~CommandFactory() {};
	unique_ptr<ICommand> create(const std::string& classname);

	unique_ptr<ICharacterCommand> createCharacterCommand(const std::string& classname);
	void registerit(const std::string& classname, ICommandCreator* creator);
private:
	std::map<std::string, ICommandCreator*> table;
};
