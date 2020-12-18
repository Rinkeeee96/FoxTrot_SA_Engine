#pragma once
#include "Events/Action/ActionEvent.h"
#include "Events\Action\OnCollisionEvent.h"
#include "Physics\PhysicsFacade.h"
#include "box2d/box2d.h"
#include <math.h>

/// @brief Contact listener for collision between objects
class ContactListenerAdapter : public b2ContactListener
{
private:
	PhysicsFacade* facade;
public:
	ContactListenerAdapter(PhysicsFacade* _facade, EventDispatcher& _dispatcher) : facade(_facade), dispatcher(_dispatcher) { }
protected:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	EventDispatcher& dispatcher;
	
	map<int, vector<Direction>> getCollisionDirection(CollisionStruct result);
};