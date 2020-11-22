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
	virtual void drawMessageAt(const ColoredText& message, const Position& pos, const ObjectSize& boundary) = 0;
	virtual void drawParticle(const ParticleData& data, int spriteID) = 0;


	virtual void setXCameraOffset(int) =0;
	virtual void setYCameraOffset(int) = 0;
	virtual int getXCameraOffset() const = 0;
	virtual int getYCameraOffset() const = 0;
private:

};
