#pragma once
#include "ParticleSystem/ParticleLib/ParticleInit.h"
#include "SceneManager/Object.h"

/// @brief 
/// Particle Bridge that inherits from Object and ParticleInit(Cocos2dx Library)
class API ParticleAdapter : public Object, public ParticleInit
{
public:
	ParticleAdapter(const int id) : Object(id, true) {};
	~ParticleAdapter() {};

	void API setPositionX(const float pos) { this->positionX = pos; setXPosition((int)pos); };
	float API getPositionX() const { return this->positionX; };

	void API setPositionY(const float pos) { this->positionY = pos; setYPosition((int)pos); };
	float API getPositionY() const { return this->positionY; };

private:

};


