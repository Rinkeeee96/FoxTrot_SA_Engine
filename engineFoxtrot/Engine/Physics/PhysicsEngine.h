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
	void onUpdate();
	void removeObject();

	Scene** pointerToCurrentScene = nullptr;

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;
	void clean();

private:
	IPhysicsFacade* physicsFacade;
	EventDispatcher* dispatcher;
	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
};
