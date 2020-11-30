#include "stdafx.h"
#include "InputEngine.h"
#include "Engine.h"

/// @brief 
InputEngine::InputEngine(Engine& _engine, shared_ptr<EventDispatcher> _dispatcher): engine(_engine), dispatcher {_dispatcher}
{
	(*dispatcher).setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(InputEngine::onKeyPressed));
}

/// @brief 
InputEngine::~InputEngine()
{
}

bool InputEngine::onKeyPressed(const Event& event) {
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);

	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_F1: {
		engine.toggleFps();
		return true;
	}
	case KeyCode::KEY_F4: {
		engine.setEngineRunning(false);
		return true;
	}
    default:
        return false;
    }
}

void InputEngine::pollEvents() {
	inputFacade->pollEvents();
}

