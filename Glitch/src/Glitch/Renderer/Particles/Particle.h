#pragma once
#include "ParticleStruct.h"

namespace Glitch {
	class GLITCH_API Particle
	{
	public:
		Particle();
		~Particle();

		void addParticle(int particleID, int width, int height, float xPosition, float yPosition, float xVelocity, float yVelocity);
		void particleMove();

		vector<ParticleStruct> particleList;

	private:


	};
}

