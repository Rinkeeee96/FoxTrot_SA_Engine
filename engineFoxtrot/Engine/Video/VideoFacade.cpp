#include "stdafx.h"
#include "VideoFacade.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#undef main

/// @brief 
VideoFacade::VideoFacade()
{
	initSDL();
}

/// @brief 
VideoFacade::~VideoFacade()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

// Tips:
// http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
/// @brief 
/// Inits SDL2
void VideoFacade::initSDL()
{
	Uint32 flags = SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Sans = TTF_OpenFont(FONT_PATH, FONT_POINT_SIZE);
	window = SDL_CreateWindow("Foxtrot Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		throw ERROR_CODE_SVIFACADE_CANT_CREATE_WINDOW;
	}
	else
	{
		//Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			throw ERROR_CODE_SVIFACADE_CANT_CREATE_RENDERER;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

			}
		}
	}
}

/// @brief 
/// Clears SDL screen
void VideoFacade::clearScreen()
{
	SDL_SetRenderDrawColor(renderer, FULL_RED, FULL_GREEN, FULL_BLUE, 0);
	SDL_RenderClear(renderer);
}

/// @brief 
/// Draws SDL screen
void VideoFacade::drawScreen()
{
	SDL_RenderPresent(renderer);
}
/// @brief 
/// Load a animated sprite into the texturemap map
/// @param spriteObject 
/// @param filename
void VideoFacade::loadImage(const SpriteObject& spriteObject) {
	if (spriteObject.getFileName() == NULL) 
		throw exception(ERRORCODES[ERROR_CODE_SVIFACADE_FILENAME_IS_NULL]);

	int textureId = spriteObject.getTextureID();

	if (textureMap[textureId] != nullptr)
		return;

	SDL_Surface* surface = IMG_Load(spriteObject.getFileName());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	textureMap[textureId] = texture;
	SDL_FreeSurface(surface);
}

SDL_Rect VideoFacade::createRect(Drawable& object) {
	SDL_Rect destination;
	int x = object.getDrawStatic() ? (int)object.getPositionX() : (int)object.getPositionX() - xCameraOffset;
	int y = object.getDrawStatic() ? (int)object.getPositionY() - (int)object.getHeight() : (int)object.getPositionY() - (int)object.getHeight() - yCameraOffset;

	destination.x = x;
	destination.y = y;
	destination.w = (int)object.getWidth();
	destination.h = (int)object.getHeight();
	return destination;
}
/// @brief 
/// Takes the sprites from the Textuture map animated and copys them to the screen
/// @param object 
void VideoFacade::renderCopy(Drawable& object)
{	
	if (object.getIsText()) {
		SDL_Rect destination = this->createRect(object);
		drawMessageAt(*object.toString(), Position(destination.x, destination.y), ObjectSize(destination.w, destination.h), true);
		return;
	}
	SpriteObject& sprite = object.GetCurrentSprite();

	if (!textureMap.count(sprite.getTextureID())) {
		loadImage(sprite);
	}
	if (textureMap[sprite.getTextureID()] == NULL)  {
		throw exception(ERRORCODES[ERROR_CODE_SVIFACADE_RENDERCOPY_SPRITE_ID_IS_NULL]);
	}
	//generate image 
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / sprite.getAnimationDelay();
	float leftpos = sprite.getLeftPos(seconds);
	int top = 0;

	//generate rectangele for selecting 1 image of a full sprite
	//leftpos = amount of pixels from the left side
	//top = amount of pixels of the top (sprites are renderd of the top to bottom
	//width = amount of pixels of the with of 1 image
	//height = amount of pixels of the height of 1 image
	SDL_Rect rect{ (int)leftpos, top, (int)sprite.getWidth(), (int)sprite.getHeight() };

	//update collision box 
	if (object.getScalable()) {
		object.setWidth(sprite.getWidth() * object.getScale());
		object.setHeight(sprite.getHeight() * object.getScale());
	}

	//generate stratch of image
	SDL_Rect destination;
	int x = object.getDrawStatic() ? (int)object.getPositionX() : (int)object.getPositionX() - xCameraOffset;
	int y = object.getDrawStatic() ? (int)object.getPositionY() - (int)object.getHeight() : (int)object.getPositionY() - (int)object.getHeight() - yCameraOffset;

	destination.x = x;
	destination.y = y;
	destination.w = (int)object.getWidth();
	destination.h = (int)object.getHeight();

	SDL_SetTextureColorMod(textureMap[sprite.getTextureID()], object.getTint().red, object.getTint().green, object.getTint().blue);
	SDL_RenderCopyEx(renderer, textureMap[sprite.getTextureID()], &rect, &destination, object.getRotation(), NULL, SDL_FLIP_NONE);
	// crude fix to draw text on top of a drawable, maybe fix with a callback function in the future, or a visitor?
	if (object.toString() != nullptr)
		drawMessageAt(*object.toString(), Position(destination.x, destination.y), ObjectSize(destination.w, destination.h));
}

/// @brief Function to draw Particles
/// @param posX 
/// @param startPosX 
/// @param posY 
/// @param startPosY 
/// @param size 
/// @param spriteID 
/// @param colorR 
/// @param colorG 
/// @param colorB 
/// @param colorA 
/// @param rotation 
void VideoFacade::drawParticle(const ParticleAdapter& part)
{
	SpriteObject& sprite = part.GetCurrentSprite();

	if (!textureMap.count(sprite.getTextureID()))
	{
		loadImage(sprite);
	}
	if (textureMap[sprite.getTextureID()] == NULL)
		throw exception(ERRORCODES[ERROR_CODE_SVIFACADE_RENDERCOPY_SPRITE_ID_IS_NULL]);


	vector<ParticleData> particleData = part.getParticleDataVector();
	for (unsigned int index = 0; index < part.getParticleCount(); index++)
	{
		auto& partData = particleData[index];

		if (partData.size <= 0 || partData.colorA <= 0)
		{
			continue;
		}
		SDL_Rect r = { int(partData.posx + partData.startPosX - partData.size / 2) - xCameraOffset, int(partData.posy + partData.startPosY - partData.size / 2) - yCameraOffset, int(partData.size), int(partData.size) };
		SDL_Color c = { Uint8(partData.colorR * 255), Uint8(partData.colorG * 255), Uint8(partData.colorB * 255), Uint8(partData.colorA * 255) };
		SDL_SetTextureColorMod(textureMap[sprite.getTextureID()], c.r, c.g, c.b);
		SDL_SetTextureAlphaMod(textureMap[sprite.getTextureID()], c.a);
		SDL_SetTextureBlendMode(textureMap[sprite.getTextureID()], SDL_BLENDMODE_BLEND);
		SDL_RenderCopyEx(renderer, textureMap[sprite.getTextureID()], nullptr, &r, partData.rotation, nullptr, SDL_FLIP_NONE);
	}
}

/// @brief
/// Draws the given text message at the given position
/// @param message
/// A Message struct containing the message and the color of the message
/// @param pos
/// @param target
/// the boundaries of the target that the text needs to be draw on top of
/// A Position struct containing the position to draw the message at
void VideoFacade::drawMessageAt(const ColoredText& message, const Position& pos, const ObjectSize& bounds, bool fromText)
{
	bool exists = std::filesystem::exists(FONT_PATH); // TODO dynamic fonts
	// TODO check if message is in bounds
	if (exists) {

		SDL_Color color = {(Uint8)message.color.red, (Uint8)message.color.green, (Uint8)message.color.blue };
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, message.text.c_str(), color);
		SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		int xPos, yPos;

		SDL_Rect message_rect;
		if (message.centered)
		{
			if (fromText) {
				// TODO check width and height positioning relative to set x/y position	
				xPos = pos.xPos + (bounds.width / 2);
				yPos = pos.yPos + (bounds.height / 2);
			}
			else {
				xPos = pos.xPos + (bounds.width / 2) - MESSAGE_WIDTH / 2;
				yPos = pos.yPos + (bounds.height / 2) - MESSAGE_HEIGHT / 2;
			}
			
		}
		else {
			// If the message doesn't fit the screen, make it fit the screen
			xPos = pos.xPos + bounds.width > WINDOW_WIDTH ? WINDOW_WIDTH - bounds.width : pos.xPos < 0 ? 0 : pos.xPos;
			yPos = pos.yPos + bounds.height > WINDOW_HEIGHT ? WINDOW_HEIGHT - bounds.height : pos.yPos < 0 ? 0 : pos.yPos;
		}
		
		if (fromText) {
			message_rect.x = xPos;
			message_rect.y = yPos;
			message_rect.w = bounds.width;
			message_rect.h = bounds.height;
		}
		else {
			message_rect.x = xPos;
			message_rect.y = yPos;
			message_rect.w = MESSAGE_WIDTH;
			message_rect.h = MESSAGE_HEIGHT;
		}

		SDL_RenderCopy(renderer, messageTexture, NULL, &message_rect);

		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(messageTexture);
	}
}

/// @brief 
void VideoFacade::clean()
{
	for (auto texture : textureMap)
	{
		SDL_DestroyTexture(texture.second);
	}
	textureMap.clear();
	xCameraOffset = 0;
	yCameraOffset = 0;
}

