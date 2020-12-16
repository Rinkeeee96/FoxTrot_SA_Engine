#include "stdafx.h"
#include "PhysicsFacade.h"
#include "PhysicsEngine.h"
#include "Events\Action\ObjectStopEvent.h"
#include "Events/Key/KeyPressed.h"
#include "Events/Action/TogglePause.h"


/// @brief Constructor
PhysicsEngine::PhysicsEngine()
{
}

/// @brief Connects the dispatcher, set the listeners for event callbacks
/// @param dispatcher 
void PhysicsEngine::start(EventDispatcher& dispatcher) {
	this->dispatcher = &dispatcher;
	physicsFacade = new PhysicsFacade(dispatcher);

	dispatcher.setEventCallback<ActionEvent>(BIND_EVENT_FN(PhysicsEngine::handleAction));
	dispatcher.setEventCallback<ObjectStopEvent>(BIND_EVENT_FN(PhysicsEngine::stopObject));

	dispatcher.setEventCallback<TogglePauseEvent>(BIND_EVENT_FN(PhysicsEngine::onPauseEvent));
};


/// @brief	Updates the physics world via the physicsFacade.
///			If the currentScene changes the physics facade will be cleaned.
void PhysicsEngine::update() {
	if (isPaused())	return;

	if (currentSceneID != (*pointerToCurrentScene)->getSceneID())
	{
		if (DEBUG_PHYSICS_ENGINE)cout << "Cleaning map and reinserting Objects" << endl;
		physicsFacade->cleanMap();
		registerObjectInCurrentVectorWithPhysicsEngine();
		currentSceneID = (*pointerToCurrentScene)->getSceneID();
	}

	physicsFacade->update();
};

/// @brief	Is called on physicsEngine shutdown.
///			Cleans the physicsEngine en deletes the physicsFacade.
void PhysicsEngine::shutdown() {
	clean();
	delete physicsFacade;
}

/// @brief Reloads the physicsFacade objects map.
void PhysicsEngine::reloadPhysicsObjects() {
	physicsFacade->cleanMap();
	registerObjectInCurrentVectorWithPhysicsEngine();
}

/// @brief Cleans the physicsFacade map
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
		case Direction::LEFT:
			this->physicsFacade->MoveLeft(objectId);
		case Direction::RIGHT:
			this->physicsFacade->MoveRight(objectId);
		case Direction::DOWN:
			this->physicsFacade->Fall(objectId);
		default:
			return false;
	}
	return false;
}

/// @brief Stops the vertical movement of an object.
/// @param event 
/// @return 
bool PhysicsEngine::stopObject(const Event& event) {
	auto& e = static_cast<const ObjectStopEvent&>(event);
	physicsFacade->stopObject(e.getObjectId(), e.getStopVertical(), e.getStopHorizontal());
	return false;
}

/// @brief Executes on pause event for physics engine
bool PhysicsEngine::onPauseEvent(const Event& event)
{
	auto pauseEvent = (TogglePauseEvent&)event;
	paused = pauseEvent.isPaused();
	return false;
}

/// @brief Destructor
/// @brief Destructor calls the shutdown function
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
