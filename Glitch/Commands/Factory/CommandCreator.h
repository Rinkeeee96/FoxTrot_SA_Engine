#pragma once
#ifndef _CREATOR_H_
#define _CREATOR_H_
class ICharacter;
class CommandCreator
{
public:
	virtual shared_ptr<ICommand> create(ICharacter* character) = 0;
};

#endif //_CREATOR_H_