#include "pch.h"
#include "CommandFactory.h"
#include "CommandCreator.h"
#include "Input/Commands/exceptions/unknownCommandException.h"

void CommandFactory::registerit(const std::string& classname, ICommandCreator* creator)
{
	table[classname] = creator;
}

ICommand* CommandFactory::create(const std::string& classname)
{
	std::map<std::string, ICommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create();
	else
		throw unknownCommandException("Unknown command " + classname);
}