#pragma once
#include "Events/Action/ActionEvent.h"
#include "IPhysicsFacade.h"

#include "SceneManager/Scene.h"
#include "General/ISubsystem.h"

#include "Fps/FrameData.h"

/// @brief Physics Engine connected to the physics facade.
class API PhysicsEngine : public ISubsystem
{
public:
	PhysicsEngine(unique_ptr<FrameData>& _frameData);
	~PhysicsEngine();

	void registerObjectInCurrentVectorWithPhysicsEngine();

	bool handleAction(const Event& event);
	bool stopObject(const Event& event);
	bool onPauseEvent(const Event& event);
	void reloadPhysicsObjects();

	unique_ptr<Scene>* pointerToCurrentScene = nullptr;

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;

	IPhysicsFacade& getIPhysicsFacade() const { return *this->physicsFacade; }
private:
	void clean();
	IPhysicsFacade* physicsFacade;
	EventDispatcher* dispatcher;

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
	unique_ptr<FrameData>& frameData;
};
