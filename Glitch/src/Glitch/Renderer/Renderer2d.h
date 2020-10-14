#pragma once
#include <Glitch\Core\Object.h>
#include "Glitch\ISystem.h"
#include <Glitch\Renderer\window.h>
#include "Glitch\Facades\SDL2\SDL2Facade.h"
#include "Glitch\Renderer\Particles\ParticleEmitter.h"
#include <filesystem>


namespace Glitch {
	class GLITCH_API Renderer2d : public ISystem
	{
	public:
		ISDL2Facade* facadeTest;
		ParticleEmitter* particleEmitter;

		Renderer2d(ISDL2Facade* rendererFacade, ParticleEmitter* _particleEmitter);
		~Renderer2d() {};

		

		void updateParticleList();

		void loadImage(int spriteID, const char* filename);
		void renderCopy(Object& object);

		// Inherited via ISystem
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		void Init(vector<Object*>* objectpointer);

	private:
		vector <Object*>* pointerToObjectVector = nullptr;
		vector <Particle*> particleList;

		void clearScreen();
		void renderParticles();
		void renderSprites();
		void drawScreen();
	};

}

