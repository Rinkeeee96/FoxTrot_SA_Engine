#pragma once
#include "SpriteObject.h"

/// @brief 
/// Object class. Object is linked with a sprite id in SVI. 

#if(EXPORT)
class DLLEXPORT Object
#else
class Object
#endif
{
public:
	Object(const int objectId);
	~Object();

	SpriteObject* GetCurrentSprite();
	int getObjectId() const;

	void setName(const std::string);
	std::string getName() const;

	void setPositionX(const float);
	float getPositionX() const;

	void setPositionY(const float);
	float getPositionY() const;

	void setRotation(const float);
	float getRotation() const;

	void setScale(const float);
	float getScale() const;

	void setDirection(const float);
	float getDirection() const;

	void setHeight(const float);
	float getHeight() const;

	void setWidth(const float);
	float getWidth() const;

	void setStatic(const bool);
	bool getStatic() const;

	void setRestitution(const float val);
	float getRestitution() const;

	void setFriction(const float val);
	float getFriction() const;

	void setDensity(const float val);
	float getDensity() const;

	void setSpeed(const float val);
	float getSpeed() const;

	void setJumpHeight(const float val);
	float getJumpHeight() const;

	bool getChanged() const;

	void registerSprite(std::string state, const SpriteObject spriteObject);
	void changeToState(const std::string state);

	void setScalable(const bool val);
	bool getScalable() const;
private:
	const int objectId = 0;
	bool scalable = false;
	SpriteObject* currentSprite;
	std::string name;
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
	std::map<std::string, SpriteObject> textures = std::map<std::string, SpriteObject>();
};