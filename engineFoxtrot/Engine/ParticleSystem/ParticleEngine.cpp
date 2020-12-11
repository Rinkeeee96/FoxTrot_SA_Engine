#include "stdafx.h"
#include "ParticleEngine.h"

/// @brief Constructor
ParticleEngine::ParticleEngine(FrameData& _frameData) : frameData{ _frameData }
{
}

/// @brief Destructor
ParticleEngine::~ParticleEngine()
{
}

void ParticleEngine::start(EventDispatcher& dispatcher)
{
}

void ParticleEngine::update()
{
	if ((*pointerToCurrentScene)->getAllDrawablesInScene().size() == 0) return;
	for (Drawable* particle : (*pointerToCurrentScene)->getAllDrawablesInScene())
	{
		if (particle != nullptr && particle->getIsParticle())
		{
			((ParticleAdapter*)particle)->update(frameData.calculateDeltaTime(DELTATIME_TIMESTEP_PHYSICS));

			checkIfObjectValueAndParticleValueMatch((ParticleAdapter&)particle);
		}
	}
}

void ParticleEngine::shutdown()
{
}

void ParticleEngine::checkIfObjectValueAndParticleValueMatch(ParticleAdapter& particle)
{
	if (particle.getPositionX() != particle.getPositionX())
	{
		particle.setPositionX(particle.getPositionX());
	}

	if (particle.getPositionY() != particle.getPositionY())
	{
		particle.setPositionY(particle.getPositionY());
	}
}


