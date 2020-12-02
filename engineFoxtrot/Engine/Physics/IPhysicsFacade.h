#pragma once
#include "PhysicsBody.h"

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

	virtual void moveLeft(const int objectId) = 0;
	virtual void moveRight(const int objectId) = 0;
	virtual void jump(const int objectId) = 0;
	virtual void fall(const int objectId) = 0;

	virtual void update() = 0;
	virtual void stopObject(int objectId) = 0;
	virtual void cleanMap() = 0;
private:

};




