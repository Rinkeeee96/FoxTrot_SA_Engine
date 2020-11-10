#pragma once
#include "SceneManager/Objects/Drawable.h"
#include "Structs/HelperStructs.h"

#include "ParticleSystem/ParticleLib/ParticleInit.h"

/// @brief Interface class for Video facade
class IVideoFacade
{
public:
	IVideoFacade() {};
	~IVideoFacade() {};

	virtual void initSDL() = 0;
	virtual void clearScreen() = 0;
	virtual void drawScreen() = 0;
	virtual void loadImage(const SpriteObject& spriteObject) = 0;
	virtual void renderCopy(Drawable& object) = 0;
	virtual void drawMessageAt(const ColoredString message, const Position pos) = 0;
	virtual void drawParticle(ParticleData data, int spriteID) = 0;


private:

};
