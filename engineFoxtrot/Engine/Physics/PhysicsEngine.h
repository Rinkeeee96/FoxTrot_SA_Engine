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

	//Set to private after testing!!!
	IPhysicsFacade* physicsFacade;
	Scene** pointerToCurrentScene = nullptr;

	void setPhysicsPause(bool value) { physicsPaused = value; };
	bool getPhysicsPauze() const { return physicsPaused; };

private:

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;

	bool physicsPaused = false;
};
