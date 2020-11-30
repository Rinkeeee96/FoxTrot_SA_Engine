#include "stdafx.h"
#include "InputEngine.h"
#include "Events/Window/WindowCloseEvent.h"
#include "Engine.h"

/// @brief 
InputEngine::InputEngine(Engine& _engine): engine(_engine)
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
		engine.toggleFps();
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

