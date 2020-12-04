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

	bool onKeyPressed(const Event& event);

	void registerObjectInCurrentVectorWithPhysicsEngine();

	bool handleAction(const Event& event);
	bool stopObject(const Event& event);
	void removeObject();

	Scene** pointerToCurrentScene = nullptr;

	void setPhysicsPaused(bool value) { physicsPaused = value; };
	bool getPhysicsPaused() const { return physicsPaused; };

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;

private:
	void clean();
	IPhysicsFacade* physicsFacade;
	EventDispatcher* dispatcher;

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;

	bool physicsPaused = false;
};
