#include "pch.h"
#include "TriggerFactory.h"
#include <Game\General\GameErrorCodes.h>

TriggerFactory::TriggerFactory(){}

void TriggerFactory::registerTrigger(string name, TriggerBase* trigger) {
	if (triggerMap.count(name) == 0) {
		triggerMap.insert(pair<std::string, TriggerBase*>(name, trigger));
	}
}

TriggerBase* TriggerFactory::create(string name, int id) {
	if (triggerMap.count(name) > 0) {
		auto clone = triggerMap[name]->clone(id);
		return clone;
	}
	throw exception(GAME_ERRORCODES[TRIGGER_NOT_FOUND]);
}