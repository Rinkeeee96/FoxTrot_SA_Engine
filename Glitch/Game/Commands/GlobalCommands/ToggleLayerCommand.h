#pragma once
#include "Game/Commands/ICharacterCommand.h"
#include "Game/Commands/GlobalCommand.h"
#include "Game/PopUps/Inventory/InventoryPopup.h"

#include "Engine/Events/Action/ToggleEventLayer.h"
class ToggleLayerCommand : public GlobalCommand
{
public:
	ToggleLayerCommand(const int _layerId, string identifier, bool _freeze = true) : GlobalCommand(_layerId, identifier, _freeze) {}
	// Inherited via ICommand
	void execute(EventDispatcher& dispatcher) override {
		ToggleLayerEvent toggleLayer(layerId);
		dispatcher.dispatchEvent<ToggleLayerEvent>(toggleLayer);
	}
};
