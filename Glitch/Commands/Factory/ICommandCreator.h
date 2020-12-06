#pragma once
class ICommand;
class ICharacter;
class ICharacterCommand;

class ICommandCreator
{
public:
	ICommandCreator() {};
	~ICommandCreator() {};

	/// <summary>
	/// Create an instance of a character command class 
	/// @param character
	/// the character that needs to be bound to the command
	virtual ICharacterCommand* createCharacterCommand(ICharacter& character) = 0;
};