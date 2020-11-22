#include "stdafx.h"
#include "InputEngine.h"
#include "Events/Window/WindowCloseEvent.h"

/// @brief 
InputEngine::InputEngine()
{
	EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(InputEngine::onKeyPressed));
}

/// @brief 
InputEngine::~InputEngine()
{
}

bool InputEngine::onKeyPressed(Event& event) {
	auto keyPressedEvent = static_cast<KeyPressedEvent&>(event);

	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_F1: {
		EventSingleton::get_instance().dispatchEvent<FpsToggleEvent>((Event&)FpsToggleEvent());
		return true;
	}
	case KeyCode::KEY_F4: {
		WindowCloseEvent event;
		EventSingleton::get_instance().dispatchEvent<WindowCloseEvent>((Event&)WindowCloseEvent());
		return true;
	}
    default:
        return false;
    }
}

void InputEngine::pollEvents() {
	inputFacade->pollEvents();
}

