#pragma once
#include "stdafx.h"
#include "KeypressInvoker.h"

void KeypressInvoker::registerCommands(KeyCode code, const ICommand& command) {
	if (isRegistered(command)) 
		throw exception("keycode already registered, cannot override");
	commands.insert(make_pair(code, make_unique<ICommand>(command)));
};

void KeypressInvoker::updateCommand(KeyCode code, ICommand& command) {

	if (! isRegistered(command))
		throw exception("trying to update an unregistered command");

	// check if the keycode for this new command has been registered
	// if so, swap them, else, register the new key for this command
	if (isRegistered(code)) {
		auto it = commands.begin();
		while (it != commands.end())
		{
			auto* registeredCommand = it->second.get();
			if (registeredCommand->getIdentifier() == command.getIdentifier())
			{
				// sla het oude commando op
				unique_ptr<ICommand> oldCommand = move(commands[code]);
				// zet het nieuwe commando op zijn plaats
				commands[code] == make_unique<ICommand>(command);
				// zet het oude command op de nu oude plek
				it->second = move(oldCommand);
			}
			++it;
		}
	}
	else
		commands[code] = make_unique<ICommand>(command);
}

void KeypressInvoker::deleteCommandThatBelongsTo(const KeyCode& keycode) {
	if (isRegistered(keycode))
	{
		commands.erase(keycode);
	}
}

void KeypressInvoker::executeCommandQueue(EventDispatcher& dispatcher)
{
	auto it = executionQueue.front();
	while (it != executionQueue.back())
	{
		KeyCode& key = executionQueue.front();
		commands[key].get()->execute(dispatcher);

		executionQueue.pop();
	}
};

void KeypressInvoker::executeCommand(const KeyCode& code) {
	if (isRegistered(code))
		executionQueue.push(code);
};


bool KeypressInvoker::isRegistered(const ICommand& command) {
	auto it = commands.begin();
	while (it != commands.end())
	{
		auto* registeredCommand = it->second.get();
		if (registeredCommand == &command) return true;
		++it;
	}
	return false;
}

bool KeypressInvoker::isRegistered(const KeyCode& keyCode) {
	return commands.find(keyCode) != commands.end();
}