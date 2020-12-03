#pragma once
#include "Drawable.h"
class PopUp : public Drawable
{
public:
	PopUp(int id, ColoredText _text, EventDispatcher& _dispatcher);
	~PopUp();

	API const ColoredText* toString() { return &text; }

private:
	EventDispatcher& dispatcher;

	ColoredText text;

};


