#include "glpch.h"
#include "SDL2Facade.h"

namespace Glitch {

	/// @brief 
	/// Inits SDL2 renderer on window
	void SDL2Facade::Init()
	{
		
	}

	void SDL2Facade::destroyScreen() {
		// Close and destroy the window
		SDL_DestroyWindow(window);
		window = NULL;

		// Clean up
		SDL_Quit();
	}

	void SDL2Facade::deallocateSurface()
	{
		//Deallocate surfaces

	}

	/// @brief 
	/// Takes the sprites from the Textuture map animated and copys them to the screen
	/// @param object 
	void SDL2Facade::renderCopy(Object& object)
	{

		// TODO
		//if (textureMap[spriteID] == NULL) throw ERROR_CODE_SVIFACADE_RENDERCOPY_SPRITE_ID_IS_NULL;
		//if (xPos == NULL) throw ERROR_CODE_SVIFACADE_RENDERCOPY_XPOS_IS_NULL;
		//if (yPos == NULL) throw ERROR_CODE_SVIFACADE_RENDERCOPY_YPOS_IS_NULL;
		//if (height == NULL) throw ERROR_CODE_SVIFACADE_RENDERCOPY_HEIGHT_IS_NULL;
		//if (width == NULL) throw ERROR_CODE_SVIFACADE_RENDERCOPY_WIDTH_IS_NULL;
		//if (rotation == NULL) throw ERROR_CODE_SVIFACADE_RENDERCOPY_ROTATION_IS_NULL;
		// TODO find out why floats ruin stuff
		SDL_Rect destination;
		destination.x = object.getPositionX();	
		destination.y = object.getPositionY() - object.getHeight();
		destination.w = object.getWidth();
		destination.h = object.getHeight();

		SpriteObject* sprite = animatedTextureMap[object.getSpriteID()];
		if (sprite == NULL) {
			throw ERROR_CODE_SDL2FACADE_SPRITE_DOESNT_EXISTS;
		}
		Uint32 ticks = SDL_GetTicks();
		Uint32 seconds = ticks / 300;
		Uint32 pos = seconds % sprite->getAmountOfTextures();
		int leftPos = pos * sprite->getWidth();
		SDL_Rect rect{ leftPos, 0, sprite->getWidth(), sprite->getHeight() };
		SDL_RenderCopy(renderer, textureMap[object.getSpriteID()], &rect, &destination);
	}

	/// @brief 
	/// Load a animated sprite into the AnimatedTexture map
	/// @param spriteID 
	/// @param filename
	/// @param height of 1 single animation sprite
	/// @param widht of 1 single animation sprite
	/// @param amount of animations of 1 sprite
	void SDL2Facade::loadSprite(int spriteID, const char* filename, int singleSpriteHeight, int singleSpriteWidth, int size) {
		if (spriteID == NULL) throw ERROR_CODE_SVIFACADE_LOADIMAGE_SPRITE_ID_IS_NULL;
		if (filename == NULL) throw ERROR_CODE_SVIFACADE_FILENAME_IS_NULL;

		SDL_Surface* surface = IMG_Load(filename);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		SpriteObject* spriteObject = new SpriteObject(spriteID, size, singleSpriteHeight, singleSpriteWidth);
		textureMap[spriteID] = texture;
		animatedTextureMap[spriteID] = spriteObject;
		SDL_FreeSurface(surface);
	}

	void SDL2Facade::createWindow(WindowProps* m_data)
	{
		// Initialize SDL2
	
		int success = SDL_Init(SDL_INIT_VIDEO);
		const char* err = SDL_GetError();

		//GL_CORE_ASSERT(success, "Could not initialize SDL2 Error: {0}");
		
		window = SDL_CreateWindow(
			m_data->Title,			// window title
			SDL_WINDOWPOS_CENTERED,	// initial x position
			SDL_WINDOWPOS_CENTERED,	// initial y position
			m_data->Width,			// width, in pixels
			m_data->Height,			// height, in pixels
			0
		);

		if (window == NULL)
		{
			GL_CORE_ERROR("Window could not be created! SDL Error: %s\n", SDL_GetError());
			throw ERROR_CODE_SVIFACADE_CANT_CREATE_WINDOW;
		}

		// set the window id in the window props struct
		m_data->Id = SDL_GetWindowID(window);
		SDL_SetWindowData(window, m_data->Title, m_data);
	}

	void SDL2Facade::createRenderer()
	{
		//Create renderer for window -- kan naar facade
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer == NULL)
		{
			GL_CORE_ERROR("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			throw ERROR_CODE_SVIFACADE_CANT_CREATE_RENDERER;
		}

		screenSurface = SDL_GetWindowSurface(window); // ?

		//Initialize PNG loading -- kan naar facade
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			GL_CORE_ERROR("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
	}

	/// @brief 
	/// Clears SDL screen
	void SDL2Facade::clearScreen()
	{
		// set draw color -> facade etc.
		SDL_SetRenderDrawColor(renderer, 2, 200, 80, 6);
		SDL_RenderClear(renderer);
	}

	/// @brief 
	/// Draws SDL screen
	void SDL2Facade::drawScreen()
	{
		SDL_RenderPresent(renderer);
	}
}