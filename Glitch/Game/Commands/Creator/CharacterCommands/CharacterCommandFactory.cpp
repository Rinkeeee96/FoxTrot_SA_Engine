#include "pch.h"
#include "CharacterCommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "CharacterCommandCreator.h"
#include "Engine/Input/Commands/exceptions/unknownCommandException.h"

void CharacterCommandFactory::registerit(const std::string& classname, ICharacterCommandCreator* creator)
{
	table[classname] = creator;
}


ICharacterCommand* CharacterCommandFactory::createCharacterCommand(const std::string& classname, ICharacter& character)
{
	auto i = table.find(classname);

	if (i != table.end())
		return i->second->createCharacterCommand(character);
	else
		throw exception(string("Unknown command " + classname).c_str());
}