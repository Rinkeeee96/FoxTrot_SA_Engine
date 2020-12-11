#pragma once
#include "Game\Triggers\BaseTrigger.h"
#include "Game\General\GameErrorCodes.h"

/// @brief Factory for triggers
class TriggerFactory {
private:
	map<string, BaseTrigger*> triggerMap;
public:
	TriggerFactory();

	void registerTrigger(string name, BaseTrigger* trigger);
	BaseTrigger* create(string name, int id);
};