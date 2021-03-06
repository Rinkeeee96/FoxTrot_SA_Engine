#include "stdafx.h"
#include "ParticleEngine.h"
#include "Events/Action/TogglePause.h"
#include "Events/EventDispatcher.h"

/// @brief Constructor
/// @param _frameData
/// A reference to the frameData class owned by Engine, used for accessing deltaTime
ParticleEngine::ParticleEngine(unique_ptr<FrameData>& _frameData) : frameData{ _frameData }
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
	dispatcher.setEventCallback<TogglePauseEvent>(BIND_EVENT_FN(ParticleEngine::onPauseEvent));
}

/// @brief  Update the particles postion. 
///			Checks if the Particle Postion is the same as the ObjectPosition
void ParticleEngine::update()
{
	if (isPaused()) return;
	
	if ((*pointerToCurrentScene)->getAllDrawablesInScene().size() == 0) return;
	for (shared_ptr<Drawable> particle : (*pointerToCurrentScene)->getAllDrawablesInScene())
	{
		if (particle != nullptr && particle->getIsParticle())
		{
			(dynamic_pointer_cast<ParticleAdapter>(particle))->update(frameData->calculateDeltaTime(DELTATIME_TIMESTEP_PHYSICS));

			checkIfObjectValueAndParticleValueMatch(dynamic_pointer_cast<ParticleAdapter>(particle));
		}
	}
}

/// @brief Does nothing. Needs to be here for syntax purpose
/// @param dispatcher 
void ParticleEngine::shutdown()
{
}

/// @brief Executes the on pause logic for the particle engine
/// @param dispatcher
bool ParticleEngine::onPauseEvent(const Event& event)
{
	auto pauseEvent = (TogglePauseEvent&)event;
	paused = pauseEvent.isPaused();
	return false;
}

/// @brief	Checks if the postion of the Particle is the same as the position of the Object.
///			If not equal they will be made equal.
///			Particle position wil be updated to the object position 
/// @param particle 
void ParticleEngine::checkIfObjectValueAndParticleValueMatch(shared_ptr<ParticleAdapter> particle)
{
	if (((shared_ptr<Object>)particle)->getPositionX() != particle->getPositionX())
	{
		particle->setPositionX(((shared_ptr<Object>)particle)->getPositionX());
	}

	if (((shared_ptr<Object>)particle)->getPositionY() != particle->getPositionY())
	{
		particle->setPositionY(((shared_ptr<Object>)particle)->getPositionY());
	}
}


