#pragma once
#include "SceneManager/Scene.h"
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "ParticleAdapter.h"
#include "General/ISubsystem.h"

/// @brief Class to update Particle
class API ParticleEngine: public ISubsystem
{
public:
	ParticleEngine();
	~ParticleEngine();

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;

	bool onPauseEvent(const Event& event);

	shared_ptr<Scene>* pointerToCurrentScene = nullptr;

private:
	void checkIfObjectValueAndParticleValueMatch(shared_ptr<ParticleAdapter> particle);

};




