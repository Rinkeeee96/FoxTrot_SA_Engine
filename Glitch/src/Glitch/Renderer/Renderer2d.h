#pragma once
#include <Glitch\Core\Object.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Glitch\ISystem.h"
#include <Glitch\Renderer\window.h>
#include "Glitch\Facades\SDL2\SDL2Facade.h"

namespace Glitch {
	class GLITCH_API Renderer2d : public ISystem
	{
	public:
		ISDL2Facade* facadeTest;

		Renderer2d(ISDL2Facade* rendererFacade) : facadeTest { rendererFacade } {};
		~Renderer2d() {};

		vector <Object*>* pointerToObjectVector = nullptr;
		void clearScreen();
		void drawScreen();
		void loadImage(int spriteID, const char* filename);
		void renderCopy(Object& object);

		// Inherited via ISystem
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		void renderSprites();
		void Init();

	private:
		//const WindowProps* windowData;
		//SDL_Window* window;
		//SDL_Surface* screenSurface;
		//SDL_Renderer* renderer;
		//unordered_map<int, SDL_Texture*> textureMap;


	};

}

