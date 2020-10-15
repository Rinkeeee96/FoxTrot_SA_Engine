#pragma once
#include "Glitch/Core/Object.h"

namespace Glitch {
	// TODO rename, SLD2 is very specific call it something like a GUIFacade
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
		virtual void loadImage(int spriteID, const char* filename) = 0;
		virtual void renderCopy(Object& object) = 0;
		//virtual void renderCopy(Glitch::Object* o) = 0;
		virtual void deallocateSurface() = 0;

		virtual void Init() = 0;


	private:

	};

}