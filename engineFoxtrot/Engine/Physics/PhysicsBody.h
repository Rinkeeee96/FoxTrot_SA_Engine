#pragma once
#include "SceneManager/Objects/Object.h"

#define DIVIDER 32.0f
#define BASE_GRAVITY 1

/// @brief This class contains all the data for a physics body
class PhysicsBody
{
public:
	API PhysicsBody(shared_ptr<Object> object);
	API ~PhysicsBody();
	API int getObjectId() const;

	API void setPositionX(const float);
	API float getPositionX() const;

	API void setPositionY(const float);
	API float getPositionY() const;

	API void setRotation(const float);
	API float getRotation() const;

	API void setHeight(const float);
	API float getHeight() const;

	API void setWidth(const float);
	API float getWidth() const;

	API void setRestitution(const float);
	API float getRestitution() const;

	API void setFriction(const float);
	API float getFriction() const;

	API void setDensity(const float);
	API float getDensity() const;

	API void setSpeed(const float);
	API float getSpeed() const;

	API void setJumpHeight(const float);
	API float getJumpHeight() const;

	API void setGravity(const float);
	API float getGravity() const;

	API void setYAxisVelocity(const float val);
	API float getYAxisVelocity() const;

	API void setXAxisVelocity(const float val);
	API float getXAxisVelocity() const;

	API void setRotatable(const bool val);
	API bool getRotatable() const;

	API shared_ptr<Object> getObject() const { return this->object; }
	API bool objectExists() const { return object != nullptr; }

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
