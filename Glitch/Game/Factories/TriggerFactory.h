#pragma once
#include <string>
#include <map>
#include <exception>
#include <Game\Triggers\TriggerBase.h>

class TriggerFactory {
private:
	map<string, TriggerBase*> triggerMap;
public:
	TriggerFactory();

	void registerTrigger(string name, TriggerBase* trigger);
	TriggerBase* create(string name, int id);
};