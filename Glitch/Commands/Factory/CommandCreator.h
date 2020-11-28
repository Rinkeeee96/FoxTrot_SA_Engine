#pragma once
#include "ICommandCreator.h"
#include "CommandFactory.h"

template <class T>
class CommandCreator : public ICommandCreator
{
public:
	CommandCreator(const string& _key) : key{ _key } {};
	~CommandCreator() {};
	void registerClass(shared_ptr<CommandFactory> factory) { factory->registerit(key, this); };
	// Inherited via ICommandCreator
	virtual shared_ptr<ICommand> create(ICharacter& character) { return shared_ptr<T>{new T(character)}; }
private:
	const string& key;

};