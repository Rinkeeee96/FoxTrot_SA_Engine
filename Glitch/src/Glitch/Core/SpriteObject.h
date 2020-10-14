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
		SpriteObject(int textureID, int size, int height, int width);
		int textureID; 
		int pos = 0;
		int size;
		int height;
		int width;

		int getCurrentTextureLeft();
	private:
	};
}