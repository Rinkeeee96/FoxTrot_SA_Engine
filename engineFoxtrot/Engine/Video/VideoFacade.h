#pragma once
#include "IVideoFacade.h"

#include "ParticleSystem/ParticleAdapter.h"

#define FONT_PATH "Assets/Fonts/Sans.ttf"
#define FONT_POINT_SIZE 24

// Forward declaration
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;
struct SDL_Rect;
typedef struct _TTF_Font TTF_Font;

/// @brief 
/// VideoFacade is de SDL2 facade
class VideoFacade : public IVideoFacade
{
public:
	VideoFacade();
	~VideoFacade();

	void initSDL();

	void clearScreen();
	void drawScreen();
	void loadImage(const SpriteObject& spriteObject);
	void renderCopy(Drawable& object, float deltaTime);

	void drawParticle(const ParticleAdapter& part);

	void drawMessageAt(const ColoredText& message, const Position& pos, const ObjectSize& target, bool fromText = false);

	void clean();
	unordered_map<int, SDL_Texture*> textureMap;

	void setXCameraOffset(int x) override { xCameraOffset = x; }
	void setYCameraOffset(int y) override { yCameraOffset = y; }
	int getXCameraOffset() const { return xCameraOffset; };
	int getYCameraOffset() const { return yCameraOffset; };
private:
	SDL_Rect createRect(Drawable& object);

	int xCameraOffset = 0;
	int yCameraOffset = 0;

	SDL_Renderer* renderer;
	SDL_Window* window;
	TTF_Font* Sans;
};
