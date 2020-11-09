#include "stdafx.h"

#include "Button.h"

void Button::mouseOver(Event& event) {
	auto mouseOverEvent = static_cast<MouseMovedEvent&>(event);
	int mousePositionX = mouseOverEvent.GetX();
	int mousePositionY = mouseOverEvent.GetY();

	isMouseOver = (mousePositionX >= positionX &&
				mousePositionX <= (positionX + width) &&
				mousePositionY >= positionY &&
				mousePositionY <= (positionY + height));
}

void Button::isClicked(Event& event) {
	auto mousePressedEvent = static_cast<MouseButtonPressed&>(event);
	if (isMouseOver && isEnabled)
		onClick();
}
