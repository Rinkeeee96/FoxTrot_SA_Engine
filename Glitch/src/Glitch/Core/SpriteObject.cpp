#include "glpch.h"
#include "SpriteObject.h"
namespace Glitch {
	SpriteObject::SpriteObject(const int _textureID, const int _size, const int _height, const int _width) : textureID(_textureID), size(_size), height(_height), width(_width)
	{
	}
	int SpriteObject::getCurrentTextureLeft() {
		this->pos = this->pos + 1;
		if (this->pos > size) {
			this->pos = 0;
		}
		return this->pos*width;
	}

}