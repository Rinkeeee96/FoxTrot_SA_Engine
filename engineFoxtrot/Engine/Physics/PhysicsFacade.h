#pragma once
#include "IPhysicsFacade.h"
#include "PhysicsBody.h"
#include "Events/Action/OnCollisionEvent.h"
#include "Fps/FrameData.h"

#define PI 3.14159f
#define TOTAL_DEGREES 180.0f

#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3

#define TIMESTEP_SEC 1.0f
#define TIMESTEP_FRAMES 60.0f

#define INCREASE_JUMP_SPEED 10
#define GRAVITY_FALL 9.8f // So when I said gravity is (0,80) that means gravity is applied at a rate of 80 pixels along the y axis per second.
#define GRAVITY_SCALE 0.0f

#define X_AXIS_STATIC 0
#define Y_AXIS_STATIC 0

struct CollisionStruct {
	PhysicsBody* object1 = nullptr;
	PhysicsBody* object2 = nullptr;
};

class b2Fixture;
class b2World;
class b2Body;

/// @brief 
/// PhysicsFacade class. Class for update physics off objects
class PhysicsFacade : public IPhysicsFacade
{
public:
	API PhysicsFacade(EventDispatcher& _dispatcher, unique_ptr<FrameData>& _frameData);
	API ~PhysicsFacade();

	API void addStaticObject(PhysicsBody* object) override;
	API void addDynamicObject(PhysicsBody* object) override;

	API PhysicsBody* getPhysicsObject(const int objectId) override;

	API void MoveLeft(const int objectId) override;
	API void MoveRight(const int objectId) override;
	API void Jump(const int objectId) override;
	API void Fall(const int objectId) override;

	API CollisionStruct getObjectsByFixture(b2Fixture* fixture1, b2Fixture* fixture2);
	API void update() override;
	API void stopObject(int objectId, bool stopVertical, bool stopHorizontal);
	API void cleanMap();

private:
	EventDispatcher& dispatcher;
	b2World * world;
	const float timeStep = TIMESTEP_SEC / TIMESTEP_FRAMES;

	// TODO clear on scene detach
	map <PhysicsBody*, b2Body*> bodies;
	b2Body* findBody(const int objectId);

	unique_ptr<FrameData>& frameData;
};
