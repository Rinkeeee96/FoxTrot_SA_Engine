#pragma once
#include "stdafx.h"
struct Color
{
	const int red;
	const int green;
	const int blue;

	Color(int _red, int _green, int _blue) :
		blue(_blue), red(_red), green(_green) {}
};

struct ColoredString
{
	ColoredString(const string& _text, const Color& _color)
		: text{ _text }, color(_color){}
	const string& text;
	const Color& color;
};

struct Position
{
	Position(int _x, int _y) : xPos{ _x }, yPos{ _y } {}
	int xPos, yPos;
};

struct ObjectSize
{
	ObjectSize(int _w, int _h) : width{ _w }, height{ _h } {}
	int width, height;
};