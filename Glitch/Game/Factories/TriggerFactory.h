#pragma once
#include "Game\Triggers\BaseTrigger.h"
#include "Game\General\GameErrorCodes.h"

/// @brief Factory for triggers
class TriggerFactory {
private:
	map<string, shared_ptr<BaseTrigger>> triggerMap;
public:
	TriggerFactory();

	void registerTrigger(string name, shared_ptr<BaseTrigger> trigger);
	shared_ptr<BaseTrigger> create(string name, int id);
};