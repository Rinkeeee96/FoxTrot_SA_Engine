#pragma once

class ICommand;
class ICharacter;
class ICommandCreator;

class CommandFactory
{
public:
	CommandFactory() {};
	~CommandFactory() {};
	shared_ptr<ICommand> create(const std::string& classname, ICharacter& character);
	void registerit(const std::string& classname, ICommandCreator* creator);
private:
	std::map<std::string, ICommandCreator*> table;
};
