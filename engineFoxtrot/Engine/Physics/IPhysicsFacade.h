#pragma once
#include "PhysicsBody.h"

/// @brief 
/// Interface facade for all physics actions
class IPhysicsFacade
{
public:
	IPhysicsFacade() {};
	virtual ~IPhysicsFacade() {};

	virtual void addStaticObject(shared_ptr<PhysicsBody> object) = 0;
	virtual void addKinamaticObject(shared_ptr<PhysicsBody> object) = 0;
	virtual void addDynamicObject(shared_ptr<PhysicsBody> object) = 0;

	virtual shared_ptr<PhysicsBody> getPhysicsObject(const int objectId) = 0;

	virtual void MoveLeft(const int objectId) = 0;
	virtual void MoveRight(const int objectId) = 0;
	virtual void Jump(const int objectId) = 0;
	virtual void Fall(const int objectId) = 0;
	virtual void updatePhysicsBody(int objId, Object& obj) = 0;
	virtual void update() = 0;
	virtual void stopObject(int objectId, bool stopVertical, bool stopHorizontal) = 0;
	virtual void cleanMap() = 0;
private:

};




