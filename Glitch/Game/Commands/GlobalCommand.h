#pragma once
#include "pch.h"
#include "Input/Commands/ICommand.h"
#include "Engine/SceneManager/Scene.h"
class GlobalCommand : public ICommand
{
public:
	GlobalCommand(int _layerId, string identifier, bool _freezeOnPause) : layerId{ _layerId }, ICommand(identifier, _freezeOnPause) {}
	virtual void execute(EventDispatcher& dispatcher) override = 0;
protected:
	int layerId;
};