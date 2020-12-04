#pragma once
#include "Drawable.h"
/// @brief Class for PopUp drawable
class PopUp : public Drawable
{
public:
	PopUp(const int id, float width, float height, float positionX, float positionY, ColoredText _text);
	PopUp(const int id, float width, float height, float positionX, float positionY, ColoredText _text, SpriteObject *spObject);
	PopUp(const int id, float width, float height, float positionX, float positionY, SpriteObject* spObject);

	~PopUp();

	API const ColoredText* toString() { return &text; }

private:
	ColoredText text;
};


