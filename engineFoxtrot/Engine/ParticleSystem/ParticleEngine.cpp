#include "stdafx.h"
#include "ParticleEngine.h"
#include "Events/Action/TogglePause.h"
#include "Events/EventDispatcher.h"

/// @brief Constructor
ParticleEngine::ParticleEngine()
{
}

/// @brief Destructor
ParticleEngine::~ParticleEngine()
{
}

void ParticleEngine::start(EventDispatcher& dispatcher)
{
	dispatcher.setEventCallback<TogglePauseEvent>(BIND_EVENT_FN(ParticleEngine::onPauseEvent));
}
// TODO listen to pause event
void ParticleEngine::update()
{
	if (isPaused()) return;
	
	if ((*pointerToCurrentScene)->getAllDrawablesInScene().size() == 0) return;
	for (Drawable* particle : (*pointerToCurrentScene)->getAllDrawablesInScene())
	{
		if (particle != nullptr && particle->getIsParticle())
		{
			((ParticleAdapter*)particle)->update();

			checkIfObjectValueAndParticleValueMatch((ParticleAdapter&)particle);
		}
	}
}

void ParticleEngine::shutdown()
{
}

bool ParticleEngine::onPauseEvent(const Event& event)
{
	auto pauseEvent = (TogglePauseEvent&)event;
	paused = pauseEvent.isPaused();
	return false;
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


