#pragma once
#include "ICommandCreator.h"
#include "CommandFactory.h"
template <class T>
class CommandCreator : public ICommandCreator
{
public:
	CommandCreator(string _key) : key{ _key } {};
	void registerClass(shared_ptr<CommandFactory> factory) { 
		factory->registerit(key, this); 
	};
	// Inherited via ICommandCreator
	ICommand* create() { return new T(key); }
private:
	string key;
};