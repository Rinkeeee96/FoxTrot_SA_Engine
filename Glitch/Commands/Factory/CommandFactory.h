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
	/// @brief
	/// Function for registrating a command creator
	/// a command is created by this creator upon request with its registered classname
	void registerit(const std::string& classname, ICommandCreator* creator);
private:
	std::map<std::string, ICommandCreator*> table;
};
