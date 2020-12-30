#include "stdafx.h"
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(shared_ptr<Object> _object) 
	:	objectID(_object->getObjectId()), height(_object->getHeight() / DIVIDER), width(_object->getWidth() / DIVIDER), posX(_object->getPositionX() / DIVIDER),
		posY(_object->getPositionY() / DIVIDER), speed(_object->getSpeed()), friction(_object->getFriction()), restitution(_object->getRestitution()), density(_object->getDensity()),
		rotation(_object->getRotation()), jumpHeight(_object->getJumpHeight()), gravity(_object->getGravity()), yAxisVelocity(_object->getYAxisVelocity()), rotatable(_object->getRotatable()), object(_object) 
{};

PhysicsBody::~PhysicsBody() { }

int PhysicsBody::getObjectId() const { return this->objectID; }

void PhysicsBody::setPositionX(const float x) { this->posX = x; this->object->setPositionX(x * DIVIDER); }
float PhysicsBody::getPositionX() const { return posX; }

void PhysicsBody::setPositionY(const float y) { this->posY = y; this->object->setPositionY(y * DIVIDER); }
float PhysicsBody::getPositionY() const { return posY; }

void PhysicsBody::setRotation(const float r) { this->rotation = r; this->object->setRotation(r); }
float PhysicsBody::getRotation() const { return rotation; }

void PhysicsBody::setHeight(const float h) { this->height = h; this->object->setHeight(h * DIVIDER);}
float PhysicsBody::getHeight() const { return height; }

void PhysicsBody::setWidth(const float w) { this->width = w; this->object->setWidth(w * DIVIDER);}
float PhysicsBody::getWidth() const { return width; }

void PhysicsBody::setRestitution(const float r) { this->restitution = r; this->object->setRestitution(r); }
float PhysicsBody::getRestitution() const { return this->restitution;}

void PhysicsBody::setFriction(const float f) { this->object->setFriction(f); }
float PhysicsBody::getFriction() const { return this->friction; }

void PhysicsBody::setDensity(const float d) { this->density = d;  this->object->setDensity(d);}
float PhysicsBody::getDensity() const { return this->density; }

void PhysicsBody::setSpeed(const float s) { this->speed = s; this->object->setSpeed(s);}
float PhysicsBody::getSpeed() const { return this->speed; }

void PhysicsBody::setJumpHeight(const float j) { this->jumpHeight = j; this->object->setJumpHeight(j);}
float PhysicsBody::getJumpHeight() const { return this->jumpHeight; }

void PhysicsBody::setGravity(const float g) { this->gravity = g; this->object->setGravity(g); }
float PhysicsBody::getGravity() const { return this->gravity; }

void PhysicsBody::setYAxisVelocity(const float val) { this->yAxisVelocity = val; this->object->setYAxisVelocity(val); }
float PhysicsBody::getYAxisVelocity() const { return this->yAxisVelocity; }

void PhysicsBody::setXAxisVelocity(const float val) { this->xAxisVelocity = val; this->object->setXAxisVelocity(val); }
float PhysicsBody::getXAxisVelocity() const { return this->xAxisVelocity; }

bool PhysicsBody::getRotatable() const { return this->rotatable; }
void PhysicsBody::setRotatable(const bool val) { this->rotatable = val; }