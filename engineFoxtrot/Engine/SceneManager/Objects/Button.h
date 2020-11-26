#pragma once
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"

// TextClass : public Drawable

class Button : public Drawable
{
public:
	API Button(int id, ColoredText _text, const function<void(void)> _onClick) :
		Drawable(id), 
		text(_text),
		onClick(_onClick)
	{
		setSize(200, 50);
		setStatic(true);
		EventSingleton::get_instance().setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
		EventSingleton::get_instance().setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
	}

	API virtual ~Button() {
		EventSingleton::get_instance().unSubscribe<MouseMovedEvent>(BIND_EVENT_FN(Button::isClicked));
		EventSingleton::get_instance().unSubscribe<MouseButtonPressed>(BIND_EVENT_FN(Button::mouseOver));
	}

	API const ColoredText* toString() { return &text; }

	API void disable() { isEnabled = false; }
	API void enable() { isEnabled = true; }

	API void setSize(float width, float height) {
		setWidth(width);
		setHeight(height);
	}

	API bool mouseOver(Event& event);
	API bool isClicked(Event& event);
	API void reset() { buttonPressed = false; }
private:
	bool isEnabled = true;
	bool isMouseOver = false;
	bool buttonPressed = false;
	void onMouseOver();

	const function<void(void)> onClick;

	ColoredText text;
};


