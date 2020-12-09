#pragma once
#include "Events/Action/ActionEvent.h"
#include "IPhysicsFacade.h"

#include "SceneManager/Scene.h"
#include "General/ISubsystem.h"

#include "Fps/FrameData.h"

class API PhysicsEngine : public ISubsystem
{
public:
	PhysicsEngine(FrameData& _frameData) : frameData{ _frameData } {};
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
	FrameData& frameData;

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
};
