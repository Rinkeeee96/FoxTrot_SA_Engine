#include "stdafx.h"
#include "Button.h"
#include <Events\Mouse\MouseMoved.h>

Button::~Button()
{
}

void Button::mouseOver(Event& event) {
	auto mouseOverEvent = static_cast<MouseMovedEvent&>(event);
	int x = mouseOverEvent.GetX();
	int y = mouseOverEvent.GetY();

	// TODO check if mouse is in bounds

}

void Button::isClicked(Event& event) {
	auto mousePressedEvent = static_cast<MouseButtonPressed&>(event);

	if (isMouseOver && isEnabled)
	{

	}
}
