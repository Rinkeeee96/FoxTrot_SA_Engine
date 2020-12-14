#pragma once
#include "Events/Action/ActionEvent.h"
#include "IPhysicsFacade.h"

#include "SceneManager/Scene.h"
#include "General/ISubsystem.h"

/// @brief Physics Engine connected to the physics facade.
class PhysicsEngine : public ISubsystem
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	API void registerObjectInCurrentVectorWithPhysicsEngine();

	API bool handleAction(const Event& event);
	API bool stopObject(const Event& event);
	API bool onPauseEvent(const Event& event);
	API void reloadPhysicsObjects();

	Scene** pointerToCurrentScene = nullptr;

	API void start(EventDispatcher& dispatcher) override;
	API void update() override;
	API void shutdown() override;

	API IPhysicsFacade& getIPhysicsFacade() const { return *this->physicsFacade; }
private:
	void clean();
	unique_ptr<IPhysicsFacade> physicsFacade;
	EventDispatcher* dispatcher;

	// CurrentScene is stored because if this changes then the objects need to be reset.
	int currentSceneID = 0;
};
