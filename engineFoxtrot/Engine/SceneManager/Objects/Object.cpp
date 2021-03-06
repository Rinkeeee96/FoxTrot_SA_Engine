#include "stdafx.h"

#include "Object.h"

/// @brief 
Object::Object(const int _objectId, const bool _isParticle) : objectId(_objectId), isParticle(_isParticle)
{
}
/// @brief 
Object::Object()
{
}
/// @brief 
Object::~Object()
{
}

// Getters and setters

int Object::getObjectId() const { return objectId; }

void Object::setPositionX(const float x) { this->positionX = x; }
float Object::getPositionX() const { return positionX; }

void Object::setPositionY(const float y) { this->positionY = y; }
float Object::getPositionY() const { return positionY; }

void Object::setRotation(const float r) { this->rotation = r; }
float Object::getRotation() const { return rotation; }

void Object::setScale(const float s) { this->scale = s; }
float Object::getScale() const { return scale; }

void Object::setHeight(const float h) { this->height = h; }
float Object::getHeight() const { return height; }

void Object::setWidth(const float w) { this->width = w; }
float Object::getWidth() const { return width; }

void Object::setStatic(const bool s) { if(s) this->staticObject = BodyType::STATIC; }
bool Object::getStatic() const { return this->staticObject == BodyType::STATIC ? true : false; }
BodyType Object::getBodyType() const { return this->staticObject;  }

float Object::getRestitution() const { return this->restitution;}
void Object::setRestitution(const float val) {this->restitution = val;}

float Object::getFriction() const {return this->friction;}
void Object::setFriction(const float val) {
	this->friction = val;
}

float Object::getDensity() const {	return this->density;}
void Object::setDensity(const float val) {this->density = val;}

float Object::getSpeed() const {return this->speed;}
void Object::setSpeed(const float val) { this->speed = val; }

float Object::getGravity() const { return this->gravity; }
void Object::setGravity(const float val) { this->gravity = val; }

float Object::getJumpHeight() const {return this->jumpHeight;}
void Object::setJumpHeight(const float val) {	this->jumpHeight = val;}

bool Object::getScalable() const { return this->scalable; }
void Object::setScalable(const bool val) { this->scalable = val; }

float Object::getYAxisVelocity() const { return this->yAxisVelocity; }
void Object::setYAxisVelocity(const float val) { this->yAxisVelocity = val; }
float Object::getXAxisVelocity() const { return this->xAxisVelocity; }
void Object::setXAxisVelocity(const float val) { this->xAxisVelocity = val; }

bool Object::getRotatable() const { return this->rotatable; }
void Object::setRotatable(const bool val) { this->rotatable = val; }

void Object::setIsRemoved(bool val) { isRemoved = val; }
bool Object::getIsRemoved() const {	return isRemoved; }


bool Object::getIsParticle() { return isParticle; }