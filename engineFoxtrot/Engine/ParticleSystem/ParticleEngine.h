#pragma once
#include "SceneManager/Scene.h"
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "ParticleAdapter.h"
#include "General/ISubsystem.h"
#include "Fps/FrameData.h"

/// @brief Class to update Particle
class API ParticleEngine: public ISubsystem
{
public:
	ParticleEngine(float* deltaTime);
	~ParticleEngine();

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;

	Scene** pointerToCurrentScene = nullptr;

private:
	void checkIfObjectValueAndParticleValueMatch(ParticleAdapter& particle);
	float* deltaTime;
};




