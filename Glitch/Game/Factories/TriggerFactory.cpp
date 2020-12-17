#include "pch.h"
#include "TriggerFactory.h"

TriggerFactory::TriggerFactory() {}

/// @brief Register trigger with its name in factory for later cloning
/// @param name 
/// @param trigger 
void TriggerFactory::registerTrigger(string name, shared_ptr<BaseTrigger> trigger) {
	if (triggerMap.count(name) == 0) {
		triggerMap.insert(pair<std::string, shared_ptr<BaseTrigger>>(name, trigger));
	}
}

/// @brief Creates an empty triger to clone to
/// @param name 
/// @param id 
/// @return 
shared_ptr<BaseTrigger> TriggerFactory::create(string name, int id) {
	if (triggerMap.count(name) > 0) {
		shared_ptr<BaseTrigger> clone = triggerMap[name]->clone(id);
		return clone;
	}
	throw exception(GAME_ERRORCODES[ENTITY_NOT_FOUND]);
}