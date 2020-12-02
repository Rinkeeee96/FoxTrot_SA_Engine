#include "pch.h"
#include "CommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "CommandCreator.h"

void CommandFactory::registerit(const std::string& classname, ICommandCreator* creator)
{
	table[classname] = creator;
}

unique_ptr<ICommand> CommandFactory::create(const std::string& classname)
{
	std::map<std::string, ICommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->create();
	else
		return (unique_ptr<ICommand>) nullptr;
}

unique_ptr<ICharacterCommand> CommandFactory::createCharacterCommand(const std::string& classname)
{
	std::map<std::string, ICommandCreator*>::iterator i;
	i = table.find(classname);

	if (i != table.end())
		return i->second->createCharacterCommand();
	else
		return (unique_ptr<ICharacterCommand>) nullptr;
}