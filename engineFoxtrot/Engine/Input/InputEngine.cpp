#include "stdafx.h"
#include "InputEngine.h"

/// @brief 
InputEngine::InputEngine()
{
#ifndef RUN_UNIT_TESTS
	EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(InputEngine::onKeyPressed));
#endif
}

/// @brief 
InputEngine::~InputEngine()
{
}

void InputEngine::onKeyPressed(Event& event) {
	auto keyPressedEvent = static_cast<KeyPressedEvent&>(event);

	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_F12:
#ifndef RUN_UNIT_TESTS
		EventSingleton::get_instance().dispatchEvent<FpsToggleEvent>((Event&)FpsToggleEvent());
#endif
		break;
	default:
		break;
	}
}

void InputEngine::pollEvents() {
	inputFacade->pollEvents();
}

