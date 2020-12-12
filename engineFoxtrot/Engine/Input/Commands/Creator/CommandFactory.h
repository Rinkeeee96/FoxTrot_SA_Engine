#pragma once
class ICommand;
class ICommandCreator;

class CommandFactory
{
public:
	/// @brief
	/// Function for creating a creator for the given classname
	virtual ICommand* create(const std::string& classname);
	/// @brief
	/// Function for registrating a command creator
	/// a command is created by this creator upon request with its registered classname
	void registerit(const std::string& classname, ICommandCreator* creator);
private:
	map<string, ICommandCreator*> table;
};
