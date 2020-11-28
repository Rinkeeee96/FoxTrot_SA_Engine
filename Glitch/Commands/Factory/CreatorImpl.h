#pragma once
#ifndef _CREATORIMPL_H_
#define _CREATORIMPL_H_

#include <string>

#include "CommandCreator.h"
#include "CommandFactory.h"

template <class T, class Factory>
class CreatorImpl : public CommandCreator
{
public:
	CreatorImpl(const string& _key) : key{ _key } {};
	~CreatorImpl() {};
	void registerClass(shared_ptr<Factory> factory) { factory->registerit(key, T); };

	shared_ptr<ICommand> create(ICharacter* character) override { return shared_ptr<T>{new T(character)}; }

private:
	const string& key;
};



#endif //_CREATORIMPL_H_