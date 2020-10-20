#include "stdafx.h"
#include "PhysicsEngine.h"

/// @brief Constructor
PhysicsEngine::PhysicsEngine()
{
}

/// @brief Destructor
PhysicsEngine::~PhysicsEngine()
{
	delete physicsFacade;
}

/// @brief 
/// A function to search a object with the ObjectId
/// If a object is not found throw PHYSICS_ENGINE_OBJECT_DOESNT_EXIST
/// @param objectId 
/// Identifier for ObjectID
Object* PhysicsEngine::getObject(const int objectId)
{
	for (Object * obj : (*pointerToCurrentScene)->getAllObjectsInScene())
	{
		if (obj->getSpriteID() == objectId)
		{
			return obj;
		}
	}
	throw PHYSICS_ENGINE_OBJECT_DOESNT_EXIST;
}

/// @brief 
/// A function to create all objects in the facade
void PhysicsEngine::registerObjectInCurrentVectorWithPhysicsEngine()
{
	if(DEBUG_PHYSICS_ENGINE)cout << "Size pointertoObj: " << (*pointerToCurrentScene)->getAllObjectsInScene().size() << endl;
	for (Object* object : (*pointerToCurrentScene)->getAllObjectsInScene())
	{
		PhysicsBody * phyObj = new PhysicsBody(object);
		if (DEBUG_PHYSICS_ENGINE)cout << "Registering object : " << phyObj->getSpriteID() << endl;

		if (object->getStatic())
		{
			physicsFacade->addStaticObject(phyObj);
		}
		else
		{
			physicsFacade->addNonStaticObject(phyObj);
		}
	}
}

/// @brief 
/// Handle the tick given from the thread. 
void PhysicsEngine::update30()
{
	if (currentSceneID != (*pointerToCurrentScene)->getSceneID())
	{
		if (DEBUG_PHYSICS_ENGINE)cout << "Cleaning map and reinserting Objects" << endl;
		physicsFacade->cleanMap();
		registerObjectInCurrentVectorWithPhysicsEngine();
		currentSceneID = (*pointerToCurrentScene)->getSceneID();
	}
	physicsFacade->update();
}

/// @brief 
/// A function to add a linearImpulse to a object for moving to left
/// @param objectId 
/// Identifier for ObjectID
void PhysicsEngine::MoveLeft(const int objectId) {
	this->physicsFacade->MoveLeft(objectId);
}

/// @brief 
/// A function to add a linearImpulse to a object for moving to right 
/// @param objectId 
/// Identifier for ObjectID
void PhysicsEngine::MoveRight(const int objectId) {
	this->physicsFacade->MoveRight(objectId);
}

/// @brief 
/// A function to add a linearImpulse to a object for jumping
/// @param objectId 
/// Identifier for ObjectID
void PhysicsEngine::Jump(const int objectId) {
	this->physicsFacade->Jump(objectId);
}

/// @brief 
/// A function to add a linearImpulse to a object for jumping to the left
/// @param objectId 
/// Identifier for ObjectID
void PhysicsEngine::JumpLeft(const int objectId) {
	this->physicsFacade->JumpLeft(objectId);
}

/// @brief 
/// A function to add a linearImpulse to a object for jumping to the right
/// @param objectId 
/// Identifier for ObjectID
void PhysicsEngine::JumpRight(const int objectId) {
	this->physicsFacade->JumpRight(objectId);
}


