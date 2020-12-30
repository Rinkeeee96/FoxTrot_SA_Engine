#pragma once
#include <string>

/// @brief 
/// Sprites coupled from other .json files
class TileSprite
{
public:

	TileSprite(std::string _path, float _width, float _height) : path{ _path }, width{ _width }, height{ _height } {};

	std::string path;
	const float width;
	const float height;
	map<string, string> properties;
};