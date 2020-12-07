#pragma once
class ICommand;
class ICharacter;
class ICharacterCommand;

class ICommandCreator
{
public:
	/// @brief
	/// Create an instance of a general command class 
	/// @param character
	/// the character that needs to be bound to the command
	virtual ICommand* create() = 0;
};