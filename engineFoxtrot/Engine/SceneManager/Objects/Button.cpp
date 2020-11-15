#include "stdafx.h"

#include "Button.h"

/// @brief 
/// A function to check if a mouse is over a button 
/// @param event
/// The mouse moved event for the mouse position. 
/// @return 
void Button::mouseOver(Event& event) {
	auto& mouseOverEvent = static_cast<MouseMovedEvent&>(event);
	int mousePositionX = mouseOverEvent.GetX();
	int mousePositionY = mouseOverEvent.GetY();

	isMouseOver = (mousePositionX >= positionX &&
				mousePositionX <= (positionX + width) &&
				mousePositionY >= (positionY - height) &&
				mousePositionY <= positionY);
}

/// @brief 
/// A function to handle a mouse click on a button
/// @param event
/// The mouse pressed event for the mouse type. 
/// @return 
void Button::isClicked(Event& event) {
	auto& mousePressedEvent = static_cast<MouseButtonPressed&>(event);
	MouseCode pressedBtn = mousePressedEvent.GetButton();
	// TODO expand functionallity, buttons only handle a primary "left click" for now
	if (isMouseOver && isEnabled && pressedBtn == MouseCode::MOUSE_BTN_LEFT)
		onClick();
}