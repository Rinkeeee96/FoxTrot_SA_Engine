#pragma once
#include <string>

class TileSprite
{
public:

	TileSprite(std::string _path, int _width, int _height) : path{ _path }, width{ _width }, height{ _height } {};

	std::string path;
	const int width;
	const int height;
};

