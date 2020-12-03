#include "stdafx.h"
#include "PopUp.h"

PopUp::PopUp(int id, ColoredText _text, EventDispatcher& _dispatcher) :
	Drawable(id),
	text(_text),
	dispatcher{ _dispatcher }
{
	setHeight(200);
	setWidth(500);

	setStatic(true);

	SpriteObject* basicPopUp = new SpriteObject(-78944, 200, 500, 20, 1, "Assets/Sprites/PopUp/BasicPopUp.png");

	registerSprite(1, basicPopUp);
	changeToState(1);

	//dispatcher.setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
	//dispatcher.setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
}

PopUp::~PopUp()
{
}