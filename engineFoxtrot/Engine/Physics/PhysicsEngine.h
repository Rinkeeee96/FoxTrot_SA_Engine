#pragma once
#include "Events\EventSingleton.h"
#include "Events/Action/ActionEvent.h"
#include "IPhysicsFacade.h"

#include "SceneManager/Scene.h"

class API PhysicsEngine
{
public:
	PhysicsEngine(shared_ptr<EventDispatcher> _dispatcher);
	~PhysicsEngine();

	void registerObjectInCurrentVectorWithPhysicsEngine();

	bool handleAction(const Event& event);
	bool stopObject(const Event& event);
	void onUpdate();
	bool removeObject(const Event& event);

	//TODO Set to private after testing!!!
	IPhysicsFacade* physicsFacade;
	Scene** pointerToCurrentScene = nullptr;

private:
	shared_ptr<EventDispatcher> dispatcher;
	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
};
