#include "stdafx.h"
#include "Button.h"

/// @brief 
/// A function to check if a mouse is over a button 
/// @param event
/// The mouse moved event for the mouse position. 
/// @return 
bool Button::mouseOver(Event& event) {
	auto& mouseOverEvent = static_cast<MouseMovedEvent&>(event);
	float mousePositionX = mouseOverEvent.GetX();
	float mousePositionY = mouseOverEvent.GetY();

	isMouseOver = (mousePositionX >= positionX &&
				mousePositionX <= (positionX + width) &&
				mousePositionY >= (positionY - height) &&
				mousePositionY <= positionY);
	if (!buttonPressed) {
		int hoverSpriteId = DEFAULT_SPRITEID;
		if (isMouseOver && hasHoverSprite) {
			hoverSpriteId = HOVER_SPRITEID;
			changeToState(hoverSpriteId);
		}
		else {
			hoverSpriteId = DEFAULT_SPRITEID;
			changeToState(hoverSpriteId);
		}
	}

	return isMouseOver;
}

/// @brief 
/// A function to handle a mouse click on a button
/// @param event
/// The mouse pressed event for the mouse type. 
/// @return 
bool Button::isClicked(Event& event) {
	if (!buttonPressed) {
		auto& mousePressedEvent = static_cast<MouseButtonPressed&>(event);
		MouseCode pressedBtn = mousePressedEvent.GetButton();
		// TODO expand functionallity, buttons only handle a primary "left click" for now
		if (isMouseOver && isEnabled && pressedBtn == MouseCode::MOUSE_BTN_LEFT) {
			onClick();
			buttonPressed = true;
			return true;
		}
	}
	return false;
}


void Button::registerHoverSprite(SpriteObject* spriteObject) {
	hasHoverSprite = true;
	int hoverSpriteId = HOVER_SPRITEID;
	Drawable::registerSprite(hoverSpriteId, spriteObject);
}