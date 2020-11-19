#pragma once
#include <string>
#include <map>
#include <exception>
#include <Game\Triggers\BaseTrigger.h>
#include <Game\General\GameErrorCodes.h>

class TriggerFactory {
private:
	map<string, BaseTrigger*> triggerMap;
public:
	TriggerFactory();

	void registerTrigger(string name, BaseTrigger* trigger);
	BaseTrigger* create(string name, int id);
};