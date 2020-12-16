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

	API void onUpdate(float deltaTime) override {};
	API void setPositionX(const float pos) { this->positionX = pos; setXPosition((int)pos); };
	API float getPositionX() const { return this->positionX; };

	API void setPositionY(const float pos) { this->positionY = pos; setYPosition((int)pos); };
	API float getPositionY() const { return this->positionY; };

	API void setWidth(float width) { this->width = width; }
	API float getWidth() const { return this->Drawable::getWidth(); }

	API void setHeight(float Height) { this->height = Height; }
	API float getHeight() const { return this->Drawable::getHeight(); }

private:

};


