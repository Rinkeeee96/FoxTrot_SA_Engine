#include "stdafx.h"
#include "InputEngine.h"
#include "Engine.h"

/// @brief 
InputEngine::InputEngine(Engine& _engine): engine(_engine)
{
}

/// @brief 
InputEngine::~InputEngine()
{
}

void InputEngine::start(EventDispatcher& dispatcher) {
	this->dispatcher = &dispatcher;
	inputFacade = new InputFacade(dispatcher);
	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(InputEngine::onKeyPressed));
};

void InputEngine::update() { 
	if(inputFacade)inputFacade->pollEvents();
};

void InputEngine::shutdown() {
	delete inputFacade;
};


bool InputEngine::onKeyPressed(const Event& event) {
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
	// TODO Send events instead of calling engine directly
	switch (keyPressedEvent.getKeyCode())
	{
	case KeyCode::KEY_F1: {
		engine.getVideoEngine().toggleFps();
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
