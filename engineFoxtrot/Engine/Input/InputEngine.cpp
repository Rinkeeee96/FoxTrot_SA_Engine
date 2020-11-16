#include "stdafx.h"
#include "InputEngine.h"

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
		case KeyCode::KEY_F12:
			EventSingleton::get_instance().dispatchEvent<FpsToggleEvent>((Event&)FpsToggleEvent());
			return true;
		default:
			return false;
	}
}

void InputEngine::pollEvents() {
	inputFacade->pollEvents();
}

