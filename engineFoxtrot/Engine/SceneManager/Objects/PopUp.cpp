#include "stdafx.h"
#include "PopUp.h"

/// @brief Constructor for PopUp with text only
/// @param id 
/// @param width 
/// @param height 
/// @param positionX 
/// @param positionY 
/// @param _text 
PopUp::PopUp( const int id, float width, float height, float positionX, float positionY, ColoredText _text) :
	Drawable(id), text(_text)
{
	setPositionX(positionX);
	setPositionY(positionY);

	setHeight(height);
	setWidth(width);

	SpriteObject* basicPopUp = new SpriteObject(-78944, 800, 800, 1, 1, "Assets/Sprites/PopUp/PopUpBlackBorder.png");

	registerSprite(1, basicPopUp);
	changeToState(1);
	setDrawStatic(true);
}

/// @brief Constructor for PopUp with text and custom SpriteObject
/// @param id 
/// @param width 
/// @param height 
/// @param positionX 
/// @param positionY 
/// @param _text 
/// @param spObject 
PopUp::PopUp(const int id, float width, float height, float positionX, float positionY, ColoredText _text, SpriteObject* spObject) :
	Drawable(id), text(_text)
{
	setPositionX(positionX);
	setPositionY(positionY);

	setHeight(height);
	setWidth(width);

	registerSprite(1, spObject);
	changeToState(1);
	setDrawStatic(true);
}

/// @brief Constructor for PopUp with SpriteObject only
/// @param id 
/// @param width 
/// @param height 
/// @param positionX 
/// @param positionY 
/// @param spObject 
PopUp::PopUp(const int id, float width, float height, float positionX, float positionY, SpriteObject* spObject) :
	Drawable(id), text("",Color(0,0,0))
{
	setPositionX(positionX);
	setPositionY(positionY);

	setHeight(height);
	setWidth(width);

	registerSprite(1, spObject);
	changeToState(1);
	setDrawStatic(true);
}

PopUp::~PopUp()
{
}