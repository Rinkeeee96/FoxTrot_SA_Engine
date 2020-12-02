#pragma once
#include "ICommandCreator.h"
#include "CommandFactory.h"

template <class T>
class CommandCreator : public ICommandCreator
{
public:
	CommandCreator(string _key) : key{ _key } {};
	~CommandCreator() {};
	void registerClass(shared_ptr<CommandFactory> factory) { 
		factory->registerit(key, this); 
	};
	// Inherited via ICommandCreator
	virtual unique_ptr<ICommand> create() { return unique_ptr<T>{new T()}; }
	virtual unique_ptr<ICharacterCommand> createCharacterCommand() { return unique_ptr<T>{new T()}; }
private:
	string key;
};