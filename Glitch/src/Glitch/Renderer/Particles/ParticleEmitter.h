#pragma once
#include "Particle.h"

namespace Glitch {
	class GLITCH_API ParticleEmitter
	{
	public:
		ParticleEmitter();
		~ParticleEmitter();


		void onUpdate();
		void createParticle(int amountOfParticles, float xPosition, float yPostion);

		vector<Particle*> getParticlesVector() {return particles;};
	private:
		vector<Particle*> particles;
	};
}


