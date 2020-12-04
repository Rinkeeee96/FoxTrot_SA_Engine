#include "stdafx.h"
#include "PopUp.h"

PopUp::PopUp( const int id, float width, float height, float positionX, float positionY, ColoredText _text) :
	Drawable(id), text( id - 1, &_text, width, height, positionX, positionY)
{
	
	setPositionX(positionX);
	setPositionY(positionY);

	setHeight(height);
	setWidth(width);

	setStatic(true);

	SpriteObject* basicPopUp = new SpriteObject(-78944, 200, 500, 1, 1, "Assets/Sprites/PopUp/BasicPopUp.png");

	registerSprite(1, basicPopUp);
	changeToState(1);
	setDrawStatic(true);
}

PopUp::~PopUp()
{
}