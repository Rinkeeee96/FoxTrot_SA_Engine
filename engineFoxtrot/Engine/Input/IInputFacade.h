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
	~IInputFacade() {};

	virtual void pollEvents() = 0;
};
