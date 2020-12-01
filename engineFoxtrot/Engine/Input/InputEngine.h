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
	API InputEngine(Engine& engine, shared_ptr<EventDispatcher> _dispatcher);
	API ~InputEngine();

	void start(EventDispatcher& dispatcher) override { };
	void update() override { };
	void shutdown() override { };

	void startup();

	void pollEvents();
private:

	Engine& engine;
	shared_ptr<EventDispatcher> dispatcher;
	IInputFacade *inputFacade;

	bool onKeyPressed(const Event& event);
};
