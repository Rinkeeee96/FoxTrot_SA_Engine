#pragma once
#include "PhysicsBody.h"

struct CollisionStruct {
	PhysicsBody* object1 = nullptr;
	PhysicsBody* object2 = nullptr;
};

class b2Fixture;
class b2World;
class b2Body;

/// @brief 
/// Interface facade for all physics actions
class IPhysicsFacade
{
public:
	IPhysicsFacade() {};
	virtual ~IPhysicsFacade() {};

	virtual void addStaticObject(PhysicsBody* object) = 0;
	virtual void addDynamicObject(PhysicsBody* object) = 0;

	virtual PhysicsBody* getPhysicsObject(const int objectId) = 0;

	virtual void MoveLeft(const int objectId) = 0;
	virtual void MoveRight(const int objectId) = 0;
	virtual void Jump(const int objectId) = 0;

	virtual CollisionStruct getObjectsByFixture(b2Fixture* fixture1, b2Fixture* fixture2) = 0;
	virtual void update() = 0;
	virtual void cleanMap() = 0;
private:

};




