#include "stdafx.h"
#include "Button.h"

/// @brief 
/// A function to check if a mouse is over a button 
/// @param event
/// The mouse moved event for the mouse position. 
/// @return 
bool Button::mouseOver(const Event& event) {
	auto mouseOverEvent = static_cast<const MouseMovedEvent&>(event);
	float mousePositionX = mouseOverEvent.getX();
	float mousePositionY = mouseOverEvent.getY();

	isMouseOver = (mousePositionX >= positionX &&
				mousePositionX <= (positionX + width) &&
				mousePositionY >= (positionY - height) &&
				mousePositionY <= positionY);

	if (!buttonPressed) {
		if (isMouseOver && hasHoverSprite) {
			changeToState(HOVER_STATE);
		}
		else {
			changeToState(DEFAULT_STATE);
		}
	}

	return false;
}

/// @brief 
/// A function to handle a mouse click on a button
/// @param event
/// The mouse pressed event for the mouse type. 
/// @return 
bool Button::isClicked(const Event& event) {
	if (!buttonPressed) {
		auto mousePressedEvent = static_cast<const MouseButtonPressed&>(event);
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


/// @brief 
/// A function to register a hover effect over a btn 
/// @param SpriteObject
/// The spriteobject with the hover effect. 
/// @return 
void Button::registerHoverSprite(SpriteObject* spriteObject) {
	hasHoverSprite = true;
	Drawable::registerSprite(HOVER_STATE, spriteObject);
}