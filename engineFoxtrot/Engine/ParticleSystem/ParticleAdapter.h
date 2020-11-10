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

private:

};


