#include "pch.h"
#include "CharacterCommandFactory.h"
#include "Game/characters/ICharacter.h"
#include "CharacterCommandCreator.h"
#include "Engine/Input/Commands/exceptions/unknownCommandException.h"
/// @brief
/// register a character command with a given identifier
/// @param classname
/// the identifier to register this creator
/// @param creator
/// the creator that holds the command instance
void CharacterCommandFactory::registerit(const std::string& classname, ICharacterCommandCreator* creator)
{
	table[classname] = creator;
}

/// @brief
/// search a character command with the given identiefier and create it
/// @param classname
/// the previously registered identifier of the command instance to find 
/// @param character
/// the character to bind to this command
ICharacterCommand* CharacterCommandFactory::createCharacterCommand(const std::string& classname, ICharacter& character)
{
	auto i = table.find(classname);

	if (i != table.end())
		return i->second->createCharacterCommand(character);
	else
		throw exception(string("Unknown command " + classname).c_str());
}