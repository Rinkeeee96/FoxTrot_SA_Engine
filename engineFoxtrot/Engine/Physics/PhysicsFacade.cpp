#include "stdafx.h"
#include "PhysicsFacade.h"
#include "./ContactListenerAdapter.h"
#include "box2d/box2d.h"

/// @brief Constructor
PhysicsFacade::PhysicsFacade(EventDispatcher& _dispatcher) : dispatcher{_dispatcher }
{
	world = new b2World(b2Vec2(GRAVITY_SCALE, GRAVITY_FALL));
	world->SetContactListener(new ContactListenerAdapter(this, _dispatcher));
}

/// @brief Destructor
PhysicsFacade::~PhysicsFacade()
{
	// When a world leaves scope or is deleted by calling delete on a pointer, all the memory reserved for bodies, fixtures, and joints is freed.This is done to improve performanceand make your life easier.
	// However, you will need to nullify any body, fixture, or joint pointers you have because they will become invalid.
	// https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_dynamics.html#autotoc_md113
}

/// @brief Returns a struct with objects that collided
/// @param fixture1 
/// @param fixture2 
/// @return 
CollisionStruct PhysicsFacade::getObjectsByFixture(b2Fixture* fixture1, b2Fixture* fixture2) {
	CollisionStruct collisionStruct = CollisionStruct();

	for (const auto& value : this->bodies) {
		for (b2Fixture* f = value.second->GetFixtureList(); f; f = f->GetNext())
		{
			if (fixture1 == f)
				collisionStruct.object1 = value.first.get();
			else if (fixture2 == f)
				collisionStruct.object2 = value.first.get();

			if (collisionStruct.object1 != nullptr && collisionStruct.object2 != nullptr) break;
		}
	}
	return collisionStruct;
}

/// @brief 
/// A function to search a physicsObject with the ObjectId
/// If a body is not found throw PHYSICS_FACADE_OBJECT_DOESNT_EXIST
/// @param objectId 
/// Identifier for ObjectID
shared_ptr<PhysicsBody> PhysicsFacade::getPhysicsObject(const int objectId)
{
	for (const auto& value : bodies) {
		if (value.first->getObjectId() == objectId)
		{
			return value.first;
		}
	}
	return nullptr;
}

/// @brief 
/// A (private) function for create a shape
/// The position is set to the bottom left
/// @param objectId 
/// Identifier for ObjectID
b2PolygonShape createShape(const PhysicsBody& object) {
	b2PolygonShape shape;
	float halfH = object.getHeight() / 2; //Box2D needs the half height of a object
	float halfW = object.getWidth() / 2; //Box2D needs the half width of a object
	float posY = object.getPositionY() - object.getHeight() / 2; //Box2d needs the middle position
	float posX = object.getPositionX() + object.getWidth() / 2; //Box2d needs the middle position
	shape.SetAsBox(halfW, halfH, b2Vec2(posX, posY), object.getRotation());
	return shape;
}

/// @brief 
/// A function for register a non static object
/// @param Object 
/// The object to register
void PhysicsFacade::addStaticObject(shared_ptr<PhysicsBody> object) {
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	b2Body* body = world->CreateBody(&groundBodyDef);


	b2PolygonShape groundBox = createShape(*object);
	body->CreateFixture(&groundBox, 0.0f);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = object->getDensity();
	fixtureDef.friction = object->getFriction();
	fixtureDef.restitution = object->getRestitution();
	if (!object->getRotatable()) body->SetFixedRotation(true);
	body->CreateFixture(&fixtureDef);

	float posY = object->getPositionY() - object->getHeight() / 2; //Box2d needs the middle position
	float posX = object->getPositionX() + object->getWidth() / 2; //Box2d needs the middle position
	groundBodyDef.position.Set(posX, posY);

	bodies.insert(pair<shared_ptr<PhysicsBody>, b2Body*>(object, body));
}

/// @brief 
/// A function for register a non static object
/// @param Object 
/// The object to register
void PhysicsFacade::addDynamicObject(shared_ptr<PhysicsBody> object)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape bodyBox = createShape(*object);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyBox;
	fixtureDef.density = object->getDensity();
	fixtureDef.friction = object->getFriction();
	fixtureDef.restitution = object->getRestitution();
	if (!object->getRotatable()) body->SetFixedRotation(true);

	body->CreateFixture(&fixtureDef);

	float posY = object->getPositionY() - object->getHeight() / 2; //Box2d needs the middle position
	float posX = object->getPositionX() + object->getWidth() / 2; //Box2d needs the middle position
	bodyDef.position.Set(posX, posY);
	bodyDef.linearVelocity = b2Vec2(0, object->getYAxisVelocity());

	if(DEBUG_PHYSICS_ENGINE)cout << "Pushing back obj: spriteid: " << object->getObjectId() << endl;
	body->SetGravityScale(object->getGravity());
	bodies.insert(pair<shared_ptr<PhysicsBody>, b2Body*>(object, body));
}

/// @brief 
/// A function to search a body with the ObjectId
/// If a body is not found throw PHYSICS_FACADE_BODY_DOESNT_EXIST
/// @param objectId 
/// Identifier for ObjectID
b2Body* PhysicsFacade::findBody(const int objectId) {
	for (const auto& value : bodies) {
		if (value.first->getObjectId() == objectId)
		{
			return value.second;
		}
	}
	return nullptr;
}

/// @brief 
/// A function to update the position information of all objects
/// The position is set to the bottom left
void PhysicsFacade::update() {
	if (!this->world) return;
	this->world->Step(timeStep, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	for (auto& it : bodies)
	{
		b2Body* body = it.second;
		if (body->GetType() == b2_staticBody) continue;

		auto object = it.first;
		if (!object) return;
		object->setPositionX(body->GetWorldCenter().x - object->getWidth() / 2);
		object->setPositionY(body->GetWorldCenter().y + object->getHeight() / 2);

		if (object->getRotatable()) object->setRotation(body->GetAngle() * (TOTAL_DEGREES / PI));
		object->setYAxisVelocity(body->GetLinearVelocity().y);
		object->setXAxisVelocity(body->GetLinearVelocity().x);
	}
}

void PhysicsFacade::stopObject(int objectId, bool stopVertical, bool stopHorizontal) {
	b2Body* body = findBody(objectId);
	auto ob = getPhysicsObject(objectId);
	if (!body || !ob) return;
	b2Vec2 vel = body->GetLinearVelocity();
	vel.y = stopVertical ? 0 : ob->getYAxisVelocity();
	vel.x = stopHorizontal ? 0 : ob->getXAxisVelocity();
	body->SetLinearVelocity(vel);
}

/// @brief 
/// A function to add a linearImpulse to a object for moving to left
/// @param objectId 
/// Identifier for ObjectID
void PhysicsFacade::MoveLeft(const int objectId)
{
	b2Body* body = findBody(objectId);
	auto ob = getPhysicsObject(objectId);
	if (!body || !ob) return;

	b2Vec2 vel = body->GetLinearVelocity();
	vel.x = ob->getSpeed() * -1;
	body->SetLinearVelocity(vel);
};

/// @brief 
/// A function to add a linearImpulse to a object for moving to right 
/// @param objectId
/// Identifier for ObjectID
void PhysicsFacade::MoveRight(const int objectId)
{
	b2Body* body = findBody(objectId);
	auto ob = getPhysicsObject(objectId);
	if (!body || !ob) return;

	b2Vec2 vel = body->GetLinearVelocity();
	vel.x = ob->getSpeed();
	body->SetLinearVelocity(vel);
};

/// @brief 
/// A function to add a linearImpulse to a object for jumping
/// @param objectId 
/// Identifier for ObjectID
void PhysicsFacade::Jump(const int objectId)
{
	b2Body* body = findBody(objectId);
	auto ob = getPhysicsObject(objectId);
	if (!body || !ob) return;

	b2Vec2 vel = body->GetLinearVelocity();
	vel.y = ob->getJumpHeight() * -1; 
	body->SetLinearVelocity(vel);
};

/// @brief 
/// A function to add a linearImpulse to a object for falling
/// @param objectId 
/// Identifier for ObjectID
void PhysicsFacade::Fall(const int objectId)
{
	b2Body* body = findBody(objectId);
	auto ob = getPhysicsObject(objectId);
	if (!body || !ob) return;

	b2Vec2 vel = body->GetLinearVelocity();
	vel.y = ob->getJumpHeight() * 1;
	body->SetLinearVelocity(vel);
};


/// @brief
/// destroy all the bodies of the world
void PhysicsFacade::cleanMap()
{
	bodies.clear();
	delete world;
	world = new b2World(b2Vec2(GRAVITY_SCALE, GRAVITY_FALL));
	world->SetContactListener(new ContactListenerAdapter(this, dispatcher));
}