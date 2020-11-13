#pragma once
#include "IVideoFacade.h"

#include "ParticleSystem/ParticleLib/ParticleInit.h"

#define FONT_PATH "Assets/Fonts/Sans.ttf"
#define FONT_POINT_SIZE 24

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;

#if(EXPORT)
class DLLEXPORT VideoFacade : public IVideoFacade
#else
/// @brief 
/// VideoFacade is de SDL2 facade
class VideoFacade : public IVideoFacade
#endif
{
public:
	VideoFacade();
	~VideoFacade();

	void initSDL();

	void clearScreen();
	void drawScreen();
	void loadImage(const SpriteObject& spriteObject);
	void renderCopy(Drawable& object);

	void drawParticle(const ParticleData& data, int spriteID);

	void drawMessageAt(const ColoredString& message, const Position& pos);

	unordered_map<int, SDL_Texture*> textureMap;

private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	TTF_Font* Sans;
};
