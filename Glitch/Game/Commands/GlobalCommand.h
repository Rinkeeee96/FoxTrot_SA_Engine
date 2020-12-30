#pragma once
#include "pch.h"
#include "Input/Commands/ICommand.h"
#include "Engine/SceneManager/Scene.h"
class GlobalCommand : public ICommand
{
public:
	GlobalCommand(int _layerId, string identifier) : layerId{ _layerId }, ICommand(identifier) {}
	GlobalCommand(string identifier) : layerId{ 0 }, ICommand(identifier) {}
	virtual void execute(EventDispatcher& dispatcher) override = 0;
protected:
	int layerId;
};