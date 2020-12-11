#include "stdafx.h"
#include "ParticleEngine.h"

/// @brief Constructor
/// @param _frameData
/// A reference to the frameData class owned by Engine, used for accessing deltaTime
ParticleEngine::ParticleEngine(FrameData& _frameData) : frameData{ _frameData }
{
}

/// @brief Destructor
ParticleEngine::~ParticleEngine()
{
}

/// @brief Does nothing. Needs to be here for syntax purpose
/// @param dispatcher 
void ParticleEngine::start(EventDispatcher& dispatcher)
{
}

/// @brief  Update the particles postion. 
///			Checks if the Particle Postion is the same as the ObjectPosition
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

/// @brief Does nothing. Needs to be here for syntax purpose
/// @param dispatcher 
void ParticleEngine::shutdown()
{
}

/// @brief	Checks if the postion of the Particle is the same as the position of the Object.
///			If not equal they will be made equal.
///			Particle position wil be updated to the object position 
/// @param particle 
void ParticleEngine::checkIfObjectValueAndParticleValueMatch(ParticleAdapter& particle)
{
	if (((Object&)particle).getPositionX() != particle.getPositionX())
	{
		particle.setPositionX(((Object&)particle).getPositionX());
	}

	if (((Object&)particle).getPositionY() != particle.getPositionY())
	{
		particle.setPositionY(((Object&)particle).getPositionY());
	}
}


