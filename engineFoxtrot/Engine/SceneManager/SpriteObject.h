#pragma once



class DLLEXPORT SpriteObject
{
public:
	SpriteObject();
	SpriteObject(const int _textureID, const float _height, const float _width, const int _size, int _animationDelay, const char * _fileName );
	~SpriteObject();
	int getTextureID() const;
	int getAmountOfTextures() const;
	float getHeight() const;
	float getWidth() const;
	const char * getFileName() const;
	float getLeftPos(uint32_t ticks);

	int getAnimationDelay();
	void setAnimationDelay(int speed);
private:
	int animationDelay = 0;
	const int textureID =0;
	const int lengthOfTextures = 0;
	const float height = 0;
	const float width = 0;
	const char * fileName;
};