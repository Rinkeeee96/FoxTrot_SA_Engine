#pragma once
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "SceneManager/Objects/Object.h"

/// @brief
/// A toggle layer event is fired when layers are shown/hidden with the given z-index 
/// before modification.
class ToggleLayerEvent : public Event
{
public:
	ToggleLayerEvent(int _layerIndex) : layerIndex{_layerIndex} {};

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	EventType getEventType() const override { return EventType::ToggleLayer; }
	/// @brief
	/// Returns the name of the event
	const char* getName() const override { return "Toggle layer event"; }

	const int getLayerIndex() { return layerIndex; }
private:
	const int layerIndex;
};