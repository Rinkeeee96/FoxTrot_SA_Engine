#include "stdafx.h"
#include "Button.h"

/// @brief Sets the default values
/// @param id 
/// @param _text 
/// @param _onClick 
/// @param _spriteObject 
/// @param _dispatcher 
Button::Button(int id, ColoredText _text, const function<void(void)> _onClick, SpriteObject* _spriteObject, EventDispatcher& _dispatcher) :
	Drawable(id), text(_text), onClick(_onClick), dispatcher{ _dispatcher }
{
	setSize(200, 50);
	setStatic(true);

	registerSprite(DEFAULT_STATE, _spriteObject);
	changeToState(DEFAULT_STATE);

	dispatcher.setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
	dispatcher.setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
}

/// @brief Sets the width and height of the buttons object
/// @param width 
/// @param height 
void Button::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}
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

	if (!buttonPressed && isEnabled) {
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