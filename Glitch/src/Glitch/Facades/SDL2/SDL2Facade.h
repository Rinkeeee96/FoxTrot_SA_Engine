#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include <unordered_map>
#include "Glitch/Renderer/WindowProps.h"
#include "Glitch/Facades/SDL2/ISDL2Facade.h"
#include <Glitch\Core\Object.h>
#include <filesystem>

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
		virtual void renderCopy(Object& object) override;
		//void renderCopy(Object* o);

		void drawMessageAt(const Message& message, const Position& pos);

		void deallocateSurface();
		SDL_Window* getWindow() { return window; }

		void Init();
		void destroyScreen();
	private:
		TTF_Font* Sans;
		SDL_Window* window;
		SDL_Surface* screenSurface;
		SDL_Renderer* renderer;
		unordered_map<int, SDL_Texture*> textureMap;
	};
}

