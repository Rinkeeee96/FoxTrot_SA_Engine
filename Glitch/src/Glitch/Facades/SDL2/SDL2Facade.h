#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <unordered_map>
#include "Glitch/Renderer/WindowProps.h"
#include "Glitch/Facades/SDL2/ISDL2Facade.h"
#include <Glitch\Core\Object.h>

#undef main
namespace Glitch {
	class GLITCH_API SDL2Facade : public ISDL2Facade
	{
	public:
		SDL2Facade() {
			Init();
		}
		~SDL2Facade() {};

		void createWindow(WindowProps* props);

		void createRenderer();
		void clearScreen();
		void drawScreen();
		void loadImage(int spriteID, const char* filename);
		void renderCopy(int spriteID, int xPos, int yPos, int width, int height, int rotation);
		//void renderCopy(Object* o);

		void deallocateSurface();
		SDL_Window* getWindow() { return window; }

		void Init();
		void destroyScreen();
	private:

		SDL_Window* window;
		SDL_Surface* screenSurface;
		SDL_Renderer* renderer;
		unordered_map<int, SDL_Texture*> textureMap;
	};
}

