#include "stdafx.h"
#include "PopUp.h"

PopUp::PopUp(int id, float width, float height, ColoredText _text) :
	Drawable(id), text(_text)
{
	setHeight(height);
	setWidth(width);

	setStatic(true);

	SpriteObject* basicPopUp = new SpriteObject(-78944, 200, 500, 1, 1, "Assets/Sprites/PopUp/BasicPopUp.png");

	registerSprite(1, basicPopUp);
	changeToState(1);
}

PopUp::~PopUp()
{
}