#pragma once
#include "IGlobalCommandCreator.h"
#include "GlobalCommandFactory.h"

template <class T>
class GlobalCommandCreator : public IGlobalCommandCreator
{
public:
	/// @brief
	/// constructor for the global command creator
	/// @param _freeze
	/// this paramter controls whether the command should be deactivated
	/// in the "pause" state, defaults to true if not overridden
	GlobalCommandCreator(string _key, bool _freeze = true) : key{ _key }, freeze{_freeze} {};
	void registerClass(shared_ptr<GlobalCommandFactory> factory) {
		factory->registerit(key, this); 
	};

	GlobalCommand* createCommand(int zIndex) override { return new T(zIndex, key, freeze); }
private:
	string key;
	bool freeze;
};