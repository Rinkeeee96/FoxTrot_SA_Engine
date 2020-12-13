#pragma once
#include "stdafx.h"
/// @brief Struct for Color, has the RGB values
struct Color
{
	int red;
	int green;
	int blue;

	Color(int _red, int _green, int _blue) :
		blue(_blue), red(_red), green(_green) {}
};

/// @brief Struct for ColoredText, has the Color struct and a Text string
struct ColoredText
{
	ColoredText(const string _text, const Color _color, bool _centered = true)
		: text{ _text }, color(_color), centered(_centered) {}
	string text;
	const Color color;
	bool centered;
};

/// @brief Postion struct containing the xPos and yPos
struct Position
{
	Position(int _x, int _y) : xPos{ _x }, yPos{ _y } {}
	int xPos, yPos;
};

/// @brief Size struct containing the width and height of an object.
struct ObjectSize
{
	ObjectSize(int _w, int _h) : width{ _w }, height{ _h } {}
	int width, height;
};