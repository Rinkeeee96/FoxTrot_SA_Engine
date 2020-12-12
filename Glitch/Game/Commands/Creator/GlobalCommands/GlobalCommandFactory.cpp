#include "pch.h"
#include "GlobalCommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "GlobalCommandCreator.h"
#include "Engine/Input/Commands/exceptions/unknownCommandException.h"

void GlobalCommandFactory::registerit(const std::string& classname, IGlobalCommandCreator* creator)
{
	table[classname] = creator;
}


GlobalCommand* GlobalCommandFactory::createCommand(const std::string& classname, const int layerIndex)
{
	auto i = table.find(classname);

	if (i != table.end())
		return i->second->createCommand(layerIndex);
	else
		throw exception(string("Unknown command " + classname).c_str());
}