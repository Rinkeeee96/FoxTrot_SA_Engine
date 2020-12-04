#pragma once
#include "Drawable.h"
class PopUp : public Drawable
{
public:
	PopUp(const int id, float width, float height, float positionX, float positionY, ColoredText _text);
	~PopUp();

	API const ColoredText* toString() { return text.toString(); }

private:
	Text *text;

};


