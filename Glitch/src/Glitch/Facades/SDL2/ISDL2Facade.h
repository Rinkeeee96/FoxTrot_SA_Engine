#pragma once
#include "Glitch/Core/Object.h"

namespace Glitch {
	class ISDL2Facade
	{
	public:
		ISDL2Facade() {};
		~ISDL2Facade() {};

		// window facade
		// renderer facade
		// facade abstraheren naar generieke functionaliteit

		virtual void createWindow(WindowProps* props) = 0;
		virtual void destroyScreen() = 0;
		virtual SDL_Window* getWindow() = 0;

		virtual void createRenderer() = 0;
		virtual void clearScreen() = 0;
		virtual void drawScreen() = 0;
		virtual void loadSprite(int spriteID, const char* filename, int singleSpriteHeight, int singleSpriteWidth, int size) = 0;
		virtual void renderCopy(Object& object) = 0;
		//virtual void renderCopy(Glitch::Object* o) = 0;
		virtual void deallocateSurface() = 0;

		virtual void Init() = 0;


	private:

	};

}