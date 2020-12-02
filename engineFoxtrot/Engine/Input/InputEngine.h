#pragma once

#include "InputFacade.h"
#include "Events/Action/ActionEvent.h"
#include "General/ISubsystem.h"

class Engine;

/// @brief 
/// Input engine for handling input
class InputEngine : public ISubsystem
{
public:
	API InputEngine(Engine& engine);
	API ~InputEngine();

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;
private:

	Engine& engine;
	IInputFacade *inputFacade;
	EventDispatcher* dispatcher;

	bool onKeyPressed(const Event& event);
};
