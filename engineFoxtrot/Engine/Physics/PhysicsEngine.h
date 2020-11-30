#pragma once
#include "Events\EventSingleton.h"
#include "Events/Action/ActionEvent.h"
#include "IPhysicsFacade.h"

#include "SceneManager/Scene.h"

class API PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void registerObjectInCurrentVectorWithPhysicsEngine();

	bool handleAction(Event& event);
	bool stopObject(Event& event);
	bool update30(Event& tick30Event);
	bool removeObject(Event& event);

	//TODO Set to private after testing!!!
	IPhysicsFacade* physicsFacade;
	Scene** pointerToCurrentScene = nullptr;

private:

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
};
