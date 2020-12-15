#include "pch.h"
#include "TriggerFactory.h"

TriggerFactory::TriggerFactory() {}

/// @brief Register trigger with its name in factory for later cloning
/// @param name 
/// @param trigger 
void TriggerFactory::registerTrigger(string name, BaseTrigger* trigger) {
	if (triggerMap.count(name) == 0) {
		triggerMap.insert(pair<std::string, BaseTrigger*>(name, trigger));
	}
	else {
		throw exception("identifier does not exist");
	}
}

/// @brief Creates an empty triger to clone to
/// @param name 
/// @param id 
/// @return 
BaseTrigger* TriggerFactory::create(string name, int id) {
	if (triggerMap.count(name) > 0) {
		auto clone = triggerMap[name]->clone(id);
		return clone;
	}
	else {
		throw exception("identifier does not exist");
	}
}