#pragma once
#include "Drawable.h"
class PopUp : public Drawable
{
public:
	PopUp(int id, float width, float height, ColoredText _text);
	~PopUp();

	API const ColoredText* toString() { return &text; }

private:
	ColoredText text;

};


