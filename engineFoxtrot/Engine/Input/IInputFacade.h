#pragma once
#include "Events/Codes/KeyCodes.h"
class Command;
/// @brief 
/// Interface Inputfacade 
class IInputFacade
{
public:
	IInputFacade() {};
	IInputFacade(EventDispatcher& _dispatcher) {};
	virtual ~IInputFacade() {};

	virtual void pollEvents() = 0;
	virtual KeyCode getSingleKeyStroke() = 0;
};
