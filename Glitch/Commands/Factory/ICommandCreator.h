#pragma once
class ICommand;
class ICharacter;
class ICharacterCommand;

class ICommandCreator
{
public:
	ICommandCreator() {};
	~ICommandCreator() {};

	virtual unique_ptr<ICommand> create() = 0;
	virtual unique_ptr<ICharacterCommand> createCharacterCommand() = 0;

};