#include "pch.h"
#include "CommandFactory.h"
#include "CommandCreator.h"

void CommandFactory::registerit(const std::string& classname, ICommandCreator* creator)
{
	table[classname] = creator;
}

ICommand* CommandFactory::create(const std::string& classname)
{
	map<string, ICommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create();
	else
		throw exception(string("Unknown command " + classname).c_str());
}