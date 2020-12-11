#pragma once
#include "IUICommandCreator.h"
#include "UICommandFactory.h"

template <class T>
class UICommandCreator : public IUICommandCreator
{
public:
	UICommandCreator(string _key) : key{ _key } {};
	void registerClass(shared_ptr<UICommandFactory> factory) { 
		factory->registerit(key, this); 
	};

	IUICommand* createUICommand(int zIndex) override { return new T(zIndex, key); }
private:
	string key;
};