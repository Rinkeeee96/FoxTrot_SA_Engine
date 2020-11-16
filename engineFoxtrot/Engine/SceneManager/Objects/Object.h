#pragma once
// TODO find out why removing this breaks everything
#include "stdafx.h"
#include "SpriteObject.h"

/// @brief 
/// Object class. Object is linked with a sprite id in SVI. 
class Object
{
public:
	API Object(const int id, const bool isParticle);
	API virtual ~Object();

	void API setPositionX(const float);
	float API getPositionX() const;
	
	API int getObjectId() const;

	void API setPositionY(const float);
	float API getPositionY() const;

	void API setRotation(const float);
	float API getRotation() const;

	void API setScale(const float);
	float API getScale() const;

	void API setHeight(const float);
	float API getHeight() const;

	void API setWidth(const float);
	float API getWidth() const;

	void API setStatic(const bool);
	bool API getStatic() const;

	void API setRestitution(const float val);
	float API getRestitution() const;

	void API setFriction(const float val);
	float API getFriction() const;

	void API setDensity(const float val);
	float API getDensity() const;

	void API setSpeed(const float val);
	float API getSpeed() const;

	void API setJumpHeight(const float val);
	float API getJumpHeight() const;

	API virtual void setYAxisVelocity(const float val);
	API float getYAxisVelocity() const;

	API virtual void setXAxisVelocity(const float val);
	API float getXAxisVelocity() const;

	API void setScalable(const bool val);
	API bool getScalable() const;

	API void setRotatable(const bool val);
	API bool getRotatable() const;

	API bool getIsParticle();
	
protected:
	// object base properties
	const int objectId = 0;

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
