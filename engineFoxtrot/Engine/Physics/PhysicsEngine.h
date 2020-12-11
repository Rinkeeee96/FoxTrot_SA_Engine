#pragma once
#include "Events/Action/ActionEvent.h"
#include "IPhysicsFacade.h"

#include "SceneManager/Scene.h"
#include "General/ISubsystem.h"

class API PhysicsEngine : public ISubsystem
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void registerObjectInCurrentVectorWithPhysicsEngine();

	bool handleAction(const Event& event);
	bool stopObject(const Event& event);
	void reloadPhysicsObjects();

	Scene** pointerToCurrentScene = nullptr;

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;

private:
	void clean();
	IPhysicsFacade* physicsFacade;
	EventDispatcher* dispatcher;

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
};
