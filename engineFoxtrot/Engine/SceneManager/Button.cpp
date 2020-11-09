#include "stdafx.h"

#include "Button.h"

void Button::mouseOver(Event& event) {
	auto& mouseOverEvent = static_cast<MouseMovedEvent&>(event);
	int mousePositionX = mouseOverEvent.GetX();
	int mousePositionY = mouseOverEvent.GetY();

	isMouseOver = (mousePositionX >= positionX &&
				mousePositionX <= (positionX + width) &&
				mousePositionY >= positionY &&
				mousePositionY <= (positionY + height));
}

void Button::isClicked(Event& event) {
	auto& mousePressedEvent = static_cast<MouseButtonPressed&>(event);
	MouseCode pressedBtn = mousePressedEvent.GetButton();
	// TODO expand functionallity, buttons only handle a primary "left click" for now
	if (isMouseOver && isEnabled && pressedBtn == MouseCode::MOUSE_BTN_LEFT)
		onClick();
}
