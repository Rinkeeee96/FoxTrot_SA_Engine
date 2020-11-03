#pragma once
// TODO find out why removing this breaks everything
#include "stdafx.h"
#include "SpriteObject.h"

/// @brief 
/// Object class. Object is linked with a sprite id in SVI. 
class API Object
{
public:
	 Object(const int id);
	 ~Object();

	void  setName(const string val);
	string  getName() const;

	int  getSpriteID() const;

	void  setPositionX(const float);
	float  getPositionX() const;
	
	 SpriteObject& GetCurrentSprite() const;
	 int getObjectId() const;

	void  setPositionY(const float);
	float  getPositionY() const;

	void  setRotation(const float);
	float  getRotation() const;

	void  setScale(const float);
	float  getScale() const;

	void  setDirection(const float);
	float  getDirection() const;

	void  setHeight(const float);
	float  getHeight() const;

	void  setWidth(const float);
	float  getWidth() const;

	void  setStatic(const bool);
	bool  getStatic() const;

	void  setRestitution(const float val);
	float  getRestitution() const;

	void  setFriction(const float val);
	float  getFriction() const;

	void  setDensity(const float val);
	float  getDensity() const;

	void  setSpeed(const float val);
	float  getSpeed() const;

	void  setJumpHeight(const float val);
	float  getJumpHeight() const;

	 virtual void setYAxisVelocity(const float val);
	 float getYAxisVelocity() const;

	 void registerSprite(int state, SpriteObject* spriteObject);
	 void changeToState(const int state);

	 void setScalable(const bool val);
	 bool getScalable() const;

	 virtual void setXAxisVelocity(const float val);
	 float getXAxisVelocity() const;

	 void setRotatable(const bool val);
	 bool getRotatable() const;

	 bool getChanged() const;
	 void setChanged(const bool c);

	 bool getIsParticle();
	
protected:

	Object(const int id, const bool particle) : objectId(id),isParticle(particle) {  }
	
	const int objectId = 0;
	SpriteObject* currentSprite = nullptr;
	string name = "";
	bool scalable = false;
	float positionX = 0;
	float positionY = 0;
	float rotation = 0;
	float scale = 0;
	float direction = 0;
	float height = 0;
	float width = 0;
	float speed = 0;
	float jumpHeight = 0;
	float density = 0;
	float friction = 0;
	float restitution = 0;
	bool staticObject = false;
	bool changed = false;
	const bool isParticle = false;
	map<const int, SpriteObject*> textures;
	bool rotatable = false;
	float yAxisVelocity = 0;
	float xAxisVelocity = 0;
};
