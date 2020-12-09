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

void InputEngine::registerKeypressInvoker(KeypressInvoker* _keypressInvoker) {
	keypressInvoker = _keypressInvoker;
}

void InputEngine::start(EventDispatcher& dispatcher) {
	this->dispatcher = &dispatcher;
	inputFacade = new InputFacade(dispatcher);
	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(InputEngine::onKeyPressed));
};

/// @brief
/// handles the updates for the input engine, pretty self explainatory
/// polls the events from the facade and if a keypressinvoker is set when using the command pattern, 
/// it handles the commands placed in queue each frame
void InputEngine::update() { 
	if(inputFacade)
		inputFacade->pollEvents();

	if (keypressInvoker)
		keypressInvoker->executeCommandQueue(*this->dispatcher);
}

void InputEngine::shutdown() {
	delete inputFacade;
};


bool InputEngine::onKeyPressed(const Event& event) {
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);

	if(keypressInvoker)
		keypressInvoker->enqueueCommand(keyPressedEvent.getKeyCode());

	return false;
}
