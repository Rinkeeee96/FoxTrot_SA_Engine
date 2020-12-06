#include "pch.h"
#include "CommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "CommandCreator.h"
#include "Commands/exceptions/unknownCommandException.h"

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

ICharacterCommand* CommandFactory::createCharacterCommand(const std::string& classname, ICharacter& character)
{
	std::map<std::string, ICommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->createCharacterCommand(character);
	else
		throw unknownCommandException("Unknown command " + classname);
}