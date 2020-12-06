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
	//ICommand* create(const std::string& classname);

	ICharacterCommand* createCharacterCommand(const std::string& classname, ICharacter& character);
	void registerit(const std::string& classname, ICommandCreator* creator);
private:
	std::map<std::string, ICommandCreator*> table;
};
