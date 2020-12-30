#include "stdafx.h"
#include "InputEngine.h"
#include "Engine.h"

/// @brief 
InputEngine::InputEngine(Engine& _engine): 
	engine(_engine)
{
}

/// @brief 
InputEngine::~InputEngine()
{
}

/// @brief Register a custom invoker
/// @param _keypressInvoker
void InputEngine::registerKeypressInvoker(KeypressInvoker* _keypressInvoker) {
	keypressInvoker = _keypressInvoker;
}

KeyCode InputEngine::getSingleKeyStroke()
{
	return inputFacade->getSingleKeyStroke();
}

/// @brief Starts the InputEngine. Setting up the inputFacade. Connecting de dispatcher.
/// @param dispatcher 
void InputEngine::start(EventDispatcher& dispatcher) {
	this->dispatcher = &dispatcher;
	inputFacade = make_unique<InputFacade>(InputFacade(dispatcher));

	dispatcher.setEventCallback<KeyPressedEvent>(onKeyPressed);
	dispatcher.setEventCallback<TogglePauseEvent>(onPause);
};

/// @brief Polls for input from the inputFacade
void InputEngine::update() { 
	if(inputFacade)
		inputFacade->pollEvents();

	if (keypressInvoker)
		keypressInvoker->executeCommandQueue(*this->dispatcher);
}