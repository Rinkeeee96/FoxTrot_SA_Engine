#pragma once
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"

#define DEFAULT_STATE				1
#define HOVER_STATE					2

class Button : public Drawable
{
public:
	API Button(int id, ColoredText _text, const function<void(void)> _onClick, SpriteObject* _spriteObject, 
		shared_ptr<EventDispatcher> _dispatcher) :
		Drawable(id), 
		text(_text),
		onClick(_onClick),
		dispatcher{_dispatcher}
	{
		setSize(200, 50);
		setStatic(true);

		registerSprite(DEFAULT_STATE, _spriteObject);
		changeToState(DEFAULT_STATE);

		(*dispatcher.get()).setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
		(*dispatcher.get()).setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
	}

	API const ColoredText* toString() { return &text; }

	API void disable() { isEnabled = false; }
	API void enable() { isEnabled = true; }

	API void setSize(float width, float height) {
		setWidth(width);
		setHeight(height);
	}

	API bool mouseOver(const Event& event);
	API bool isClicked(const Event& event);

	API void registerHoverSprite(SpriteObject* spriteObject);

protected:
	bool hasHoverSprite = false;

private:
	bool isEnabled = true;
	bool isMouseOver = false;
	bool buttonPressed = false;

	const function<void(void)> onClick;

	shared_ptr<EventDispatcher> dispatcher;

	ColoredText text;
};


