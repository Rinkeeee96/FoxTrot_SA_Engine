#pragma once
#include <Glitch\Core\Object.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "Glitch\ISystem.h"
#include <Glitch\Renderer\window.h>
#include "Glitch\Facades\SDL2\SDL2Facade.h"
#include <filesystem>
#include <GLitch\FPS\FrameData.h>

#define NO_RED 0
#define NO_BLUE 0
#define NO_GREEN 0

#define X_ZERO 0
#define Y_ZERO 0
#define SDL_FPS_Y 36

namespace Glitch {
	class GLITCH_API Renderer2d : public ISystem
	{
	public:
		ISDL2Facade* facadeTest;
		
		void toggleFps();
		Renderer2d(ISDL2Facade* rendererFacade) : facadeTest { rendererFacade } {};
		~Renderer2d() {};

		vector <Object*>* pointerToObjectVector = nullptr;
		void clearScreen();
		void drawScreen();
		void drawFps();
		void drawFps(double fps, int x, int y, const string& prefix);
		void loadImage(int spriteID, const char* filename);
		void renderCopy(Object& object);

		// Inherited via ISystem
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		void renderSprites();
		void Init(vector<Object*>* objectpointer);

	private:
		bool shouldDrawFps;
		FrameData* frameData;
		//const WindowProps* windowData;
		//SDL_Window* window;
		//SDL_Surface* screenSurface;
		//SDL_Renderer* renderer;
		//unordered_map<int, SDL_Texture*> textureMap;


	};

}

