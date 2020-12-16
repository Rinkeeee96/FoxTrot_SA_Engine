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
	API VideoFacade();
	API ~VideoFacade();

	void initSDL();

	void clearScreen();
	void drawScreen();
	API void loadImage(const shared_ptr<SpriteObject> spriteObject);
	API void renderCopy(shared_ptr<Drawable>);

	void drawParticle(shared_ptr<ParticleAdapter> part);

	void drawMessageAt(const ColoredText& message, const Position& pos, const ObjectSize& target, bool fromText = false);

	void clean();
	unordered_map<int, SDL_Texture*> textureMap;

	void setXCameraOffset(int x) override { xCameraOffset = x; }
	void setYCameraOffset(int y) override { yCameraOffset = y; }
	int getXCameraOffset() const { return xCameraOffset; };
	int getYCameraOffset() const { return yCameraOffset; };
private:
	SDL_Rect createRect(shared_ptr<Drawable> object);

	int xCameraOffset = 0;
	int yCameraOffset = 0;

	SDL_Renderer* renderer;
	SDL_Window* window;
	TTF_Font* Sans;
};
