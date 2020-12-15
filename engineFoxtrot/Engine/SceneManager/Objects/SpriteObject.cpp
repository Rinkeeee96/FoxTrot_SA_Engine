#include "stdafx.h"
#include "SpriteObject.h"

SpriteObject::SpriteObject(const int _textureID, const float _height, const float _width, const int _size, int _animationDelay, const char* _fileName) :
							textureID(_textureID), height(_height), width(_width), lengthOfTextures(_size), animationDelay(_animationDelay), fileName(_fileName){};
SpriteObject::~SpriteObject() {};

int SpriteObject::getTextureID() const { return textureID; }
int SpriteObject::getAmountOfTextures() const { return lengthOfTextures; }
float SpriteObject::getHeight() const { return height; }
float SpriteObject::getWidth() const { return width; }
const char * SpriteObject::getFileName() const { return fileName; }

int SpriteObject::getAnimationDelay() { return animationDelay; }
void SpriteObject::setAnimationDelay(int delay) { animationDelay = delay; }

/// @brief 
/// A function to freeze the animation on a specifick sprite
/// for animation the freezenumber needs to be -1;
/// @param number
/// Identifier of free frame 
void SpriteObject::freeze(int number = -1) {
	freezedAnimation = number;
}

/// @brief 
/// A function to freeze the animation when a sprite has reached a specifick sprite
/// for animation the freezenumber needs to be -1;
/// @param number
/// Identifier of free frame 
void SpriteObject::freezeOn(int number = -1) {
	freezeBy = number;
}


/// @brief 
/// A function to give the left position of the sprite
/// @param tick
/// Identifier of the tick of a frame. 
/// @return 
/// a left poition of full texture
float SpriteObject::getLeftPos(uint32_t tick){
	if (freezedAnimation != -1) {
		// -1 this is because we count from 0 and not from 1
		return width * (freezeBy - 1);
	}
	if (freezeBy != -1 && freezeBy-1 <= currentAnimation) {
		// -1 this is because we count from 0 and not from 1
		return width * (freezeBy-1);
	}

	uint32_t pos = tick % lengthOfTextures;
	currentAnimation = pos;
	return pos * width;
}

float SpriteObject::getLeftPos(float deltaTime)
{
	animationTimer += deltaTime * 1000;

	if (freezedAnimation != -1) {
		// -1 this is because we count from 0 and not from 1
		return width * (freezeBy - 1);
	}
	if (freezeBy != -1 && freezeBy - 1 <= currentAnimation) {
		// -1 this is because we count from 0 and not from 1
		return width * (freezeBy - 1);
	}

	uint32_t pos = (int)(animationTimer / animationDelay) % lengthOfTextures;
	currentAnimation = pos;
	return pos * width;
}
