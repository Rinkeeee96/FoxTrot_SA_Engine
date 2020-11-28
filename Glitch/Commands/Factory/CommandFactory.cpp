#include "pch.h"
#include "CommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "CommandCreator.h"

void CommandFactory::registerit(const std::string& classname, ICommandCreator* creator)
{
	table[classname] = creator;
}

shared_ptr<ICommand> CommandFactory::create(const std::string& classname, ICharacter& character)
{
	std::map<std::string, ICommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create(character);
	else
		return (shared_ptr<ICommand>) nullptr;
}