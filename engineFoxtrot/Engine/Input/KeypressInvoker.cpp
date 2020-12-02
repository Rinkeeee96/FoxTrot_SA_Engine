#pragma once
#include "stdafx.h"
#include "KeypressInvoker.h"

void KeypressInvoker::registerCommands(KeyCode code, unique_ptr<ICommand> command) {
	if (isRegistered(command)) 
		throw exception("keycode already registered, cannot override");
	commands[code] = move(command);
};

void KeypressInvoker::updateCommand(KeyCode code, unique_ptr<ICommand> command) {

	if (! isRegistered(command))
		throw exception("trying to update an unregistered command");

	// check if the keycode for this new command has been registered
	// if so, swap them, else, register the new key for this command
	if (isRegistered(code))
		std::swap(commands[code], command);
	else
		commands[code] = move(command);
}
void KeypressInvoker::executeCommandQueue(EventDispatcher& dispatcher)
{
	auto it = executionQueue.front();
	while (it != executionQueue.back())
	{
		KeyCode key = executionQueue.front();
		executionQueue.pop();

		commands[key].get()->execute(dispatcher);
	}
};

void KeypressInvoker::executeCommand(KeyCode code) {
	if (isRegistered(code) && commands[code].get()->isEnabled())
		executionQueue.push(code);
};


bool KeypressInvoker::isRegistered(unique_ptr<ICommand>& command) {
	auto it = commands.begin();
	while (it != commands.end())
	{
		if (it->second == command)
		{
			return true;
		}
		++it;
	}
	return false;
}

bool KeypressInvoker::isRegistered(const KeyCode& keyCode) {
	return commands.find(keyCode) != commands.end();
}