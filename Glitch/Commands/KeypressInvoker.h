#pragma once
#include "pch.h"
#include "ICharacterCommand.h"
class KeypressInvoker
{
public:
	KeypressInvoker();
	~KeypressInvoker();

	void registerCommands(KeyCode code, ICommand command);
	void executeCommand(KeyCode code);

private:
	unordered_map<KeyCode, ICommand*> playerCommands;
	ICharacter* player;
};

KeypressInvoker::KeypressInvoker()
{
}

KeypressInvoker::~KeypressInvoker()
{
}