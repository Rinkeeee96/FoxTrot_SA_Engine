#pragma once
#include "Events/Codes/KeyCodes.h"
#include "./Events/Key/KeyPressed.h"
#include "./Events/Key/KeyReleased.h"
#include "./Events/Mouse/MouseMoved.h"
#include "./Events/Mouse/MousePressed.h"
#include "./Events/Mouse/MouseReleased.h"
#include "./Events/Mouse/MouseScrolledEvent.h"

#include "IInputFacade.h"

union SDL_Event;

/// @brief Facade for SDL input part
class InputFacade : public IInputFacade
{
public:
    InputFacade(EventDispatcher& _dispatcher) : dispatcher{ _dispatcher } {};
    ~InputFacade() {};

	void pollEvents() override;
    KeyCode getSingleKeyStroke() override;

private:
    EventDispatcher& dispatcher;
};