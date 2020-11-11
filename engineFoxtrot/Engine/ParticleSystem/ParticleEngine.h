#pragma once
#include "SceneManager/Scene.h"
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "ParticleAdapter.h"

/// @brief Class to update Particle
class API ParticleEngine

{
public:
	ParticleEngine();
	~ParticleEngine();


	void onUpdate(Event& tickEvent);


	Scene** pointerToCurrentScene = nullptr;

private:
	void checkIfObjectValueAndParticleValueMatch(ParticleAdapter& particle);

};




