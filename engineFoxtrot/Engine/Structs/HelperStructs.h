#pragma once
#include "stdafx.h"
struct Color
{
	int red;
	int green;
	int blue;

	Color(int _red, int _green, int _blue) :
		blue(_blue), red(_red), green(_green) {}
};

struct ColoredText
{
	ColoredText(const string _text, const Color _color, bool _centered = true)
		: text{ _text }, color(_color), centered(_centered) {}
	const string text;
	const Color color;
	bool centered;
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