#pragma once
#include "Events/Codes/KeyCodes.h"
#include "Events/EventDispatcher.h"
#include "ICommand.h"
#include <queue>
class KeypressInvoker
{
public:
	API KeypressInvoker() {
		commands.clear();
	};
	API virtual ~KeypressInvoker() {};
	API void registerCommand(KeyCode code, ICommand* command);
	API virtual void updateCommand(KeyCode code, const string& identifier);
	API void deleteCommandThatBelongsTo(const KeyCode& code);
	API void executeCommandQueue(EventDispatcher& dispatcher);
	API void enqueueCommand(const KeyCode& code);
	API ICommand* getCommandByIdentifier(const string& identifier);

protected:
	API bool isRegistered(const ICommand& command);
	API bool isRegistered(const KeyCode& keyCode);
private:
	unordered_map<KeyCode, ICommand*> commands;
	queue<KeyCode> executionQueue;
};