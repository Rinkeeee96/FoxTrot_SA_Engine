#pragma once

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <string>
#include <map>
class ICommand;
class Creator;
class ICharacter;

class CommandFactory
{
public:
	CommandFactory() {};
	~CommandFactory() {};
	shared_ptr<ICommand> create(const std::string& classname, ICharacter* character);
	void registerit(const std::string& classname, CommandCreator* creator);
private:
	std::map<std::string, CommandCreator*> table;
};

#endif //_FACTORY_H_
