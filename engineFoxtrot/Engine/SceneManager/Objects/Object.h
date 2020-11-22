#pragma once
#include "core.h"
#include "SpriteObject.h"

/// @brief 
/// Object class. Object is linked with a sprite id in SVI. 
class Object
{
public:
	API Object(const int id, const bool isParticle);
	API Object();
	API ~Object();

	API void setPositionX(const float);
	API float getPositionX() const;
	
	API int getObjectId() const;

	API void setPositionY(const float);
	API float getPositionY() const;

	API void setRotation(const float);
	API float getRotation() const;

	API void setScale(const float);
	API float getScale() const;
	
	API void setHeight(const float);
	API float getHeight() const;
	
	API void setWidth(const float);
	API float getWidth() const;
	
	API void setStatic(const bool);
	API bool getStatic() const;
	
	API void setRestitution(const float val);
	API float getRestitution() const;
	
	API void setFriction(const float val);
	API float getFriction() const;
	
	API void setDensity(const float val);
	API float getDensity() const;
	
	API void setSpeed(const float val);
	API float getSpeed() const;
	
	API void setJumpHeight(const float val);
	API float getJumpHeight() const;

	API virtual void setYAxisVelocity(const float val);
	API float getYAxisVelocity() const;

	API virtual void setXAxisVelocity(const float val);
	API float getXAxisVelocity() const;

	API void setScalable(const bool val);
	API bool getScalable() const;

	API void setRotatable(const bool val);
	API bool getRotatable() const;

	API void setIsRemoved(bool val);
	API bool getIsRemoved() const;

	API bool getIsParticle();

	virtual void onUpdate() = 0;
	
protected:
	// object base properties
	const int objectId = 0;
	bool isRemoved = false;

	bool scalable = false;
	float positionX = 0;
	float positionY = 0;
	float height = 0;
	float width = 0;

	bool rotatable = false;
	float rotation = 0;
	float scale = 0;

	// -----------------
	// movable / physics properties
	float speed = 0;
	float jumpHeight = 0;
	float yAxisVelocity = 0;
	float xAxisVelocity = 0;
	float density = 0;
	float friction = 0;
	float restitution = 0;
	bool staticObject = false;
	// ----------------
	// unknown
	bool changed = false;
	const bool isParticle = false;
};
