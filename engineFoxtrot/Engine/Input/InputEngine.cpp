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

/// @brief Starts the InputEngine. Setting up the inputFacade. Connecting de dispatcher.
/// @param dispatcher 
void InputEngine::start(EventDispatcher& dispatcher) {
	this->dispatcher = &dispatcher;
	inputFacade = new InputFacade(dispatcher);
	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(InputEngine::onKeyPressed));
};

/// @brief Polls for input from the inputFacade
void InputEngine::update() { 
	if(inputFacade)
		inputFacade->pollEvents();

	if (keypressInvoker)
		keypressInvoker->executeCommandQueue(*this->dispatcher);
}

/// @brief Deletes the inputFacade
void InputEngine::shutdown() {
	if (inputFacade)
	{
		delete inputFacade;
	}
};

/// @brief	Function is called when a keyPressed event is fired.
///			If F1 is pressed FPS is toggled
///			If F4 is pressed the game will shutdown
/// @param event 
/// @return 
bool InputEngine::onKeyPressed(const Event& event) {
	auto& keyPressedEvent = static_cast<const KeyPressedEvent&>(event);

	if(keypressInvoker)
		keypressInvoker->enqueueCommand(keyPressedEvent.getKeyCode());

	return false;
}
