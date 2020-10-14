#include "glpch.h"
#include "Renderer2d.h"

namespace Glitch {

	/// @brief 
	/// Inits SDL2 renderer on window
	void Renderer2d::Init(vector<Object*>* objectpointer)
	{
		this->pointerToObjectVector = objectpointer;
		facadeTest->createRenderer();
	}

	void Renderer2d::OnUpdate()
	{
		updateParticleList();
		clearScreen();
		renderSprites();
		drawScreen();
	}

	void Renderer2d::Shutdown()
	{
		facadeTest->deallocateSurface();
	}

	void Renderer2d::renderSprites()
	{
		if (pointerToObjectVector == nullptr) return;
		//if (pointerToObjectVector->capacity() <= 0) return;
		for (Object* obj : *pointerToObjectVector) {
			if (obj != nullptr) {
				facadeTest->renderCopy(*obj);
			}
		}
	}

	Renderer2d::Renderer2d(ISDL2Facade* rendererFacade, ParticleEmitter* _particleEmitter)
	{
		facadeTest = rendererFacade;
		particleEmitter = _particleEmitter;
	}

	/// @brief 
	/// Clears SDL screen
	void Renderer2d::clearScreen()
	{
		facadeTest->clearScreen();
	}

	void Renderer2d::renderParticles()
	{
		
	}

	/// @brief 
	/// Draws SDL screen
	void Renderer2d::drawScreen()
	{
		facadeTest->drawScreen();
	}

	void Renderer2d::updateParticleList()
	{
		particleList = particleEmitter->getParticlesVector();
	}

	/// @brief 
	/// Loads PNG files and makes them textures to be added to the unordered map
	/// @param spriteID 
	/// @param filename 
	void Renderer2d::loadImage(int spriteID, const char* filename)
	{
		// TODO error if file cannot be found
		bool exists = std::filesystem::exists(filename);
		facadeTest->loadImage(spriteID, filename);
	}

	/// @brief 
	/// Takes the sprites from the Textuture map and copys them to the screen
	/// @param spriteID 
	/// @param xPos 
	/// @param yPos 
	/// @param width 
	/// @param height 
	/// @param rotation 
	void Renderer2d::renderCopy(Object& object)
	{
		facadeTest->renderCopy(object);
	}
}