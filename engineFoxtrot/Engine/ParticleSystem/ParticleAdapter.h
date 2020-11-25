#pragma once
#include "ParticleSystem/ParticleLib/ParticleInit.h"
#include "SceneManager/Objects/Drawable.h"

/// @brief 
/// Particle Bridge that inherits from Object and ParticleInit(Cocos2dx Library)
class ParticleAdapter : public Drawable, public ParticleInit
{
public:
	API ParticleAdapter(const int id) : Drawable(id, true) {};
	API ~ParticleAdapter() {};

	API void onUpdate() override {};
	void API setPositionX(const float pos) { this->positionX = pos; setXPosition((int)pos); };
	float API getPositionX() const { return this->positionX; };

	void API setPositionY(const float pos) { this->positionY = pos; setYPosition((int)pos); };
	float API getPositionY() const { return this->positionY; };

	void setWidth(float width) { this->width = width; }
	float getWidth() const { return this->getWidth(); }

	void setHeight(float Height) { this->height = Height; }
	float getHeight() const { return this->getHeight(); }

private:

};


