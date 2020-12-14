#pragma once
class ICharacter;
class ICharacterCommand;

class ICharacterCommandCreator
{
public:
	/// @brief
	/// Create an instance of a character command class 
	/// @param character
	/// the character that needs to be bound to the command
	virtual ICharacterCommand* createCharacterCommand(ICharacter& character) = 0;
};