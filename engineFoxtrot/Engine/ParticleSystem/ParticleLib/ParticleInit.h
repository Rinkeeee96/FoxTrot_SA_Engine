#pragma once
#include "Particle.h"
#include "SceneManager/Objects/Object.h"

class ParticleInit : public Particle
{
public:
    ParticleInit(){};
    virtual ~ParticleInit() {}

    enum class ParticleStyle
    {
        NONE,
        FIRE,
        FIRE_WORK,
        SUN,
        GALAXY,
        FLOWER,
        METEOR,
        SPIRAL,
        EXPLOSION,
        SMOKE,
        SNOW,
        RAIN,
        TORCH
    };

    ParticleStyle style_ = ParticleStyle::NONE;
    API void setStyle(ParticleStyle style);
};
