#pragma once
#include "Events/Codes/KeyCodes.h"
class Command;
/// @brief 
/// Interface Inputfacade 
class IInputFacade
{
public:
	IInputFacade() {};
	IInputFacade(shared_ptr<EventDispatcher> _dispatcher) {};
	~IInputFacade() {};

	virtual void pollEvents() = 0;
};
