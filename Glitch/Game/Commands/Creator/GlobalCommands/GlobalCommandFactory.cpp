#include "pch.h"
#include "GlobalCommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "GlobalCommandCreator.h"
/// @brief
/// register a command with a given identifier
void GlobalCommandFactory::registerit(const std::string& classname, IGlobalCommandCreator* creator)
{
	table[classname] = creator;
}

/// @brief
/// search a command with the given identiefier and create it
/// @param classname
/// the previously registered identifier of the command instance to find 
/// @param layerIndex
/// the layerindex to bind this command to
GlobalCommand* GlobalCommandFactory::createCommand(const std::string& classname, const int layerIndex)
{
	auto i = table.find(classname);

	if (i != table.end())
		return i->second->createCommand(layerIndex);
	else
		throw exception(string("Unknown command " + classname).c_str());
}