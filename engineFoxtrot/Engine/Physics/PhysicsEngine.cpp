#include "stdafx.h"
#include <Events\AppTickEvent30.h>
#include "Events/EventSingleton.h"
#include "PhysicsFacade.h"
#include "PhysicsEngine.h"
#include <Events\Action\ObjectStopEvent.h>

/// @brief Constructor
PhysicsEngine::PhysicsEngine()
{
	physicsFacade = new PhysicsFacade();
	EventSingleton::get_instance().setEventCallback<AppTickEvent30>(BIND_EVENT_FN(PhysicsEngine::update30));
	EventSingleton::get_instance().setEventCallback<ActionEvent>(BIND_EVENT_FN(PhysicsEngine::handleAction));
	EventSingleton::get_instance().setEventCallback<ObjectStopEvent>(BIND_EVENT_FN(PhysicsEngine::stopObject));
}

/// @brief 
/// Handles a ActionEvent and according to the given direction moves the object
void PhysicsEngine::handleAction(Event& event) {
	auto actionEvent = static_cast<ActionEvent&>(event);

	auto direction = actionEvent.GetDirection();
	auto objectId = actionEvent.GetObjectId();
	switch (direction)
	{
		case Direction::UP:
			this->physicsFacade->Jump(objectId);
		break;
		case Direction::LEFT:
			this->physicsFacade->MoveLeft(objectId);
			break;
		case Direction::RIGHT:
			this->physicsFacade->MoveRight(objectId);
			break;
		default:
			break;
	}
}

void PhysicsEngine::stopObject(Event& event) {
	ObjectStopEvent e = static_cast<ObjectStopEvent&>(event);
	physicsFacade->stopObject(e.GetObjectId());
}

/// @brief Destructor
PhysicsEngine::~PhysicsEngine()
{
	delete physicsFacade;
}

/// @brief 
/// A function to create all objects in the facade
void PhysicsEngine::registerObjectInCurrentVectorWithPhysicsEngine()
{
	if(DEBUG_PHYSICS_ENGINE)cout << "Size pointertoObj: " << (*pointerToCurrentScene)->getAllObjectsInSceneRenderPhysics().size() << endl;
	for (Object* object : (*pointerToCurrentScene)->getAllObjectsInSceneRenderPhysics())
	{
		PhysicsBody * phyObj = new PhysicsBody(object);
		if (DEBUG_PHYSICS_ENGINE)cout << "Registering object : " << phyObj->getObjectId() << endl;
		if (object->getIsParticle()) continue;
		if (object->getStatic())
		{
			physicsFacade->addStaticObject(phyObj);
		}
		else
		{
			physicsFacade->addDynamicObject(phyObj);
		}
	}
}

/// @brief 
/// Handle the tick given from the thread. 
void PhysicsEngine::update30(Event& tick30Event)
{
	if (currentSceneID != (*pointerToCurrentScene)->getSceneID())
	{
		if (DEBUG_PHYSICS_ENGINE)cout << "Cleaning map and reinserting Objects" << endl;
		physicsFacade->cleanMap();
		registerObjectInCurrentVectorWithPhysicsEngine();
		currentSceneID = (*pointerToCurrentScene)->getSceneID();
	}
	//tick30Event = (AppTickEvent30&)tick30Event;
	physicsFacade->update();
}


