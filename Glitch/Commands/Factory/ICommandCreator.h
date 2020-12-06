#pragma once
class ICommand;
class ICharacter;
class ICharacterCommand;

class ICommandCreator
{
public:
	ICommandCreator() {};
	~ICommandCreator() {};

	//virtual ICommand* create() = 0;
	virtual ICharacterCommand* createCharacterCommand(ICharacter& character) = 0;
};