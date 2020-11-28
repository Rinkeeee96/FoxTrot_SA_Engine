#pragma once
class ICommandCreator
{
public:
	ICommandCreator() {};
	~ICommandCreator() {};

	virtual shared_ptr<ICommand> create(ICharacter& character) = 0;

};