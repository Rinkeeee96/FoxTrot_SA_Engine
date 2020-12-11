#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/Commands/IUICommand.h"
#include "Game/PopUps/Inventory/InventoryPopup.h"

#include "Engine/Events/Action/ToggleEventLayer.h"
class ToggleLayerCommand : public IUICommand
{
public:
	ToggleLayerCommand(const int _layerId, string identifier) : IUICommand(_layerId, identifier) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		ToggleLayerEvent toggleLayer(layerId);
		dispatcher.dispatchEvent<ToggleLayerEvent>(toggleLayer);
	}
};
