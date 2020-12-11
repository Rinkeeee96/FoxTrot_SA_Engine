#pragma once
#include "pch.h"
#include "Input/Commands/ICommand.h"
#include "Engine/SceneManager/Scene.h"
class IUICommand : public ICommand
{
public:
	IUICommand(int _layerId, string identifier) : layerId{ _layerId }, ICommand(identifier) {}
	virtual void execute(EventDispatcher& dispatcher) override = 0;
protected:
	int layerId;
};