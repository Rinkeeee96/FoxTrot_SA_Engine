#pragma once

#include "InputFacade.h"
#include "Events/Action/ActionEvent.h"
#include "Events/Action/TogglePause.h"
#include "General/ISubsystem.h"
#include "Input/Commands/KeypressInvoker.h"

class Engine;

/// @brief 
/// Input engine for handling input
class InputEngine : public ISubsystem
{
public:
	API InputEngine(Engine& engine);
	API ~InputEngine();

	API void registerKeypressInvoker(KeypressInvoker* _keypressInvoker);
	API KeyCode getSingleKeyStroke();

	API void start(EventDispatcher& dispatcher) override;
	API void update() override;
	API void shutdown() override {};
private:

	Engine& engine;
	unique_ptr<IInputFacade> inputFacade;
	EventDispatcher* dispatcher = nullptr;

	KeypressInvoker* keypressInvoker = nullptr;

	/// @brief	Function is called when a keyPressed event is fired.
	/// If F1 is pressed FPS is toggled
	/// If F4 is pressed the game will shutdown
	EventCallbackFn onKeyPressed = [this](const Event& event)-> bool {
		auto& keyPressedEvent = static_cast<const KeyPressedEvent&>(event);

		if (keypressInvoker)
			keypressInvoker->enqueueCommand(keyPressedEvent.getKeyCode());

		return false;
	};

	EventCallbackFn onPause = [this](const Event& event)-> bool {
		auto& pauseEvent = (TogglePauseEvent&)event;
		if (keypressInvoker)
		{
			if (pauseEvent.isPaused())
				this->keypressInvoker->pause();
			else
				this->keypressInvoker->unpause();
		}
		return false;
	};
};
