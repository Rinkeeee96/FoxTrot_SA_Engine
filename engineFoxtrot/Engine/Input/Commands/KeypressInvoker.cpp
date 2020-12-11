#pragma once
#include "stdafx.h"
#include "KeypressInvoker.h"
#include "Engine.h"

void KeypressInvoker::registerCommand(KeyCode code, ICommand* command) {
	if (isRegistered(*command)) 
		throw exception("keycode already registered, cannot override");
	commands.insert(make_pair(code, command));
};

void KeypressInvoker::updateCommand(KeyCode code, ICommand* command) {

	if (! isRegistered(*command))
		throw exception("trying to update an unregistered command");

	// check if the keycode for this new command has been registered
	// if so, swap them, else, register the new key for this command
	if (isRegistered(code)) {
		for (pair<KeyCode, ICommand*> registeredCommand : commands)
		{

			if (registeredCommand.second->getIdentifier() == command->getIdentifier())
			{
				swap(registeredCommand.second, command);
				return;
			}
		}
	}
	else
		commands[code] = command;
}

void KeypressInvoker::deleteCommandThatBelongsTo(const KeyCode& keycode) {
	if (isRegistered(keycode))
	{
		commands.erase(keycode);
	}
}

void KeypressInvoker::executeCommandQueue(EventDispatcher& dispatcher)
{
	for (size_t i = 0; i < executionQueue.size(); i++)
	{
		KeyCode& key = executionQueue.front();
		commands[key]->execute(dispatcher);

		executionQueue.pop();
	}
};

void KeypressInvoker::enqueueCommand(const KeyCode& code) {
	if (isRegistered(code))
		executionQueue.push(code);
};


bool KeypressInvoker::isRegistered(const ICommand& command) {
	auto it = commands.begin();
	while (it != commands.end())
	{
		if (it->second == &command) return true;
		++it;
	}
	return false;
}

bool KeypressInvoker::isRegistered(const KeyCode& keyCode) {
	return commands.find(keyCode) != commands.end();
}