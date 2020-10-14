#pragma once
#include "Glitch/Core/Core.h"
#include "glpch.h"
using namespace std;
namespace Glitch {
	/// @brief 
/// Object class. Object is linked with a sprite id in SVI. 
	class GLITCH_API SpriteObject
	{
	public:
		SpriteObject(const int _textureID, const int _size, const int _height, const int _width) : textureID(_textureID), lengthOfTextures(_size), height(_height), width(_width) {}

		int getTextureID() const;
		int getAmountOfTextures() const;
		int getHeight() const;
		int getWidth() const;
	private:
		int textureID;
		int lengthOfTextures;
		int height;
		int width;
	};
}