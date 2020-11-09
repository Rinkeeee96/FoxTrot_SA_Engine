#include "stdafx.h"

#include "Button.h"

void Button::mouseOver(Event& event) {
	//auto mouseOverEvent = (MouseMovedEvent&) event;
	//int x = mouseOverEvent.GetX();
	//int y = mouseOverEvent.GetY();

	// TODO check if mouse is in bounds

}

void Button::isClicked(Event& event) {
	auto mousePressedEvent = static_cast<MouseButtonPressed&>(event);
	if (isMouseOver && isEnabled)
		onClick();
}
