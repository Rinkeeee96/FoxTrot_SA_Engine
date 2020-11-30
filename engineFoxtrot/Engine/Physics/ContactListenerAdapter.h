#pragma once
#include "Events/Action/ActionEvent.h"
#include "Events\Action\OnCollisionEvent.h"
#include "Physics\PhysicsFacade.h"
#include "box2d/box2d.h"
#include <math.h>

class ContactListenerAdapter : public b2ContactListener
{
private:
	PhysicsFacade* facade;
public:
	ContactListenerAdapter(PhysicsFacade* _facade, shared_ptr<EventDispatcher> _dispatcher) : facade(_facade) { }
protected:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	shared_ptr<EventDispatcher> dispatcher;
	
	map<int, vector<Direction>> getCollisionDirection(CollisionStruct result);
};