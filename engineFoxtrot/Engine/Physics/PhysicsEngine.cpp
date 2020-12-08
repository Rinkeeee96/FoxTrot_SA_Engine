#include "stdafx.h"
#include "PhysicsFacade.h"
#include "PhysicsEngine.h"
#include "Events\Action\ObjectStopEvent.h"
#include "Events/Key/KeyPressed.h"


/// @brief Constructor
PhysicsEngine::PhysicsEngine()
{
}

void PhysicsEngine::start(EventDispatcher& dispatcher) {
	this->dispatcher = &dispatcher;
	physicsFacade = new PhysicsFacade(dispatcher);

	dispatcher.setEventCallback<ActionEvent>(BIND_EVENT_FN(PhysicsEngine::handleAction));
	dispatcher.setEventCallback<ObjectStopEvent>(BIND_EVENT_FN(PhysicsEngine::stopObject));
};



void PhysicsEngine::update() {
	if (currentSceneID != (*pointerToCurrentScene)->getSceneID())
	{
		if (DEBUG_PHYSICS_ENGINE)cout << "Cleaning map and reinserting Objects" << endl;
		physicsFacade->cleanMap();
		registerObjectInCurrentVectorWithPhysicsEngine();
		currentSceneID = (*pointerToCurrentScene)->getSceneID();
	}

	physicsFacade->update();
};

void PhysicsEngine::shutdown() {
	clean();
	delete physicsFacade;
};

void PhysicsEngine::reloadPhysicsObjects() {
	physicsFacade->cleanMap();
	registerObjectInCurrentVectorWithPhysicsEngine();
}

/// @brief 
void PhysicsEngine::clean()
{
	if (physicsFacade)
		physicsFacade->cleanMap();
	
}

/// @brief 
/// Handles a ActionEvent and according to the given direction moves the object
bool PhysicsEngine::handleAction(const Event& event) {
	auto actionEvent = static_cast<const ActionEvent&>(event);

	auto direction = actionEvent.getDirection();
	auto objectId = actionEvent.getObjectId();
	switch (direction)
	{
		case Direction::UP:
			this->physicsFacade->Jump(objectId);
			return true;
		case Direction::LEFT:
			this->physicsFacade->MoveLeft(objectId);
			return true;
		case Direction::RIGHT:
			this->physicsFacade->MoveRight(objectId);
			return true;
		case Direction::DOWN:
			this->physicsFacade->Fall(objectId);
			return true;
		default:
			// TODO what should handle action do when it fails? does the eventhandler need to continue?
			return false;
	}
}

bool PhysicsEngine::stopObject(const Event& event) {
	ObjectStopEvent e = static_cast<const ObjectStopEvent&>(event);
	physicsFacade->stopObject(e.getObjectId(), e.getStopVertical());
	return true;
}

/// @brief Destructor
PhysicsEngine::~PhysicsEngine()
{
	shutdown();
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
		if (object->getIsRemoved()) continue;
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


