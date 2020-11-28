#include "pch.h"
#include "CommandCreator.h"
#include "CommandFactory.h"
#include "Game/characters/ICharacter.h"
void CommandFactory::registerit(const std::string& classname, CommandCreator* creator)
{
	table[classname] = creator;
}

shared_ptr<ICommand> CommandFactory::create(const std::string& classname, ICharacter* character)
{
	std::map<std::string, CommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create(character);
	else
		return (shared_ptr<ICommand>) nullptr;
}