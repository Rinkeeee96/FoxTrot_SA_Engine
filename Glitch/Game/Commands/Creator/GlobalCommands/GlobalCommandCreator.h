#pragma once
#include "IGlobalCommandCreator.h"
#include "GlobalCommandFactory.h"

template <class T>
class GlobalCommandCreator : public IGlobalCommandCreator
{
public:
	GlobalCommandCreator(string _key) : key{ _key } {};
	void registerClass(shared_ptr<GlobalCommandFactory> factory) {
		factory->registerit(key, this); 
	};

	GlobalCommand* createCommand(int zIndex) override { return new T(zIndex, key); }
private:
	string key;
};