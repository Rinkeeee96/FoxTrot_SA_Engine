#pragma once

#include "PhysicsFacade.h"
#include "../Events/EventManager.h"
#include "../SceneManager/Scene.h"

#if(EXPORT)
class DLLEXPORT PhysicsEngine : public EventListener
#else
class PhysicsEngine : public EventListener
#endif
{
public:
	EventManager* eventManager{ new EventManager };

	Scene** pointerToCurrentScene = nullptr;

	PhysicsEngine();
	~PhysicsEngine();

	void registerObjectInCurrentVectorWithPhysicsEngine();

	void MoveLeft(const int objectId);
	void MoveRight(const int objectId);
	void Jump(const int objectId);
	void JumpLeft(const int objectId);
	void JumpRight(const int objectId);

	void update30();

	void update(Object* object) override {
		std::cout << "Handle notification " << std::endl;
	}

	//Set to private after testing!!!
	IPhysicsFacade * physicsFacade = new PhysicsFacade;
private:

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
	Object* getObject(const int objectId);
};





