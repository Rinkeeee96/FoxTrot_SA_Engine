#include "pch.h"
#include "TriggerFactory.h"

TriggerFactory::TriggerFactory() {}

void TriggerFactory::registerTrigger(string name, BaseTrigger* trigger) {
	if (triggerMap.count(name) == 0) {
		triggerMap.insert(pair<std::string, BaseTrigger*>(name, trigger));
	}
}

BaseTrigger* TriggerFactory::create(string name, int id) {
	if (triggerMap.count(name) > 0) {
		auto clone = triggerMap[name]->clone(id);
		return clone;
	}
	throw exception(GAME_ERRORCODES[ENTITY_NOT_FOUND]);
}