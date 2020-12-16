#pragma once
#include "SceneManager/Objects/Object.h"

#define DIVIDER 32.0f
#define BASE_GRAVITY 1

/// @brief This class contains all the data for a physics body
class API PhysicsBody
{
public:
	PhysicsBody(shared_ptr<Object> object);
	~PhysicsBody();
	int getObjectId() const;

	void setPositionX(const float);
	float getPositionX() const;

	void setPositionY(const float);
	float getPositionY() const;

	void setRotation(const float);
	float getRotation() const;

	void setHeight(const float);
	float getHeight() const;

	void setWidth(const float);
	float getWidth() const;

	void setRestitution(const float);
	float getRestitution() const;

	void setFriction(const float);
	float getFriction() const;

	void setDensity(const float);
	float getDensity() const;

	void setSpeed(const float);
	float getSpeed() const;

	void setJumpHeight(const float);
	float getJumpHeight() const;

	void setGravity(const float);
	float getGravity() const;

	void setYAxisVelocity(const float val);
	float getYAxisVelocity() const;

	void setXAxisVelocity(const float val);
	float getXAxisVelocity() const;

	void setRotatable(const bool val);
	bool getRotatable() const;

	shared_ptr<Object> getObject() const { return this->object; }
	bool objectExists() const { return object != nullptr; }

protected:
	int objectID = 0;
	float height = 0;
	float width = 0;
	float posX = 0;
	float posY = 0;
	float speed = 0;
	float friction = 0;
	float restitution = 0;
	float density = 0;
	float rotation = 0;
	float jumpHeight = 0;
	float gravity = BASE_GRAVITY;
	shared_ptr<Object> object = nullptr;
	float yAxisVelocity = 0;
	float xAxisVelocity = 0;
	bool rotatable = false;
};
