#pragma once
#include "Events/EventSingleton.h"
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Object.h"
#include "Structs/Color.h"

class API Button : public Object
{
public:
	Button(int id, string _text, Color _color, const function<void(void)> _onClick) :
		Object(id), 
		color(_color), 
		text(_text),
		onClick(_onClick)
	{
		setStatic(true);
		isMouseOver = true;
		EventSingleton::get_instance().setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
		EventSingleton::get_instance().setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
	}

	const string& getText() { return text; }
	const Color& getColor() { return color; }

	void updateText(string updatedText) { text = updatedText; }

	void disable() { isEnabled = false; }
	void enable() { isEnabled = true; }

	void setSize(int width, int height) {
		setWidth(width);
		setHeight(height);
	}

	void mouseOver(Event& event);
	void isClicked(Event& event);

private:
	bool isEnabled = true;
	bool isMouseOver = false;

	const function<void(void)> onClick;

	Color color;
	string text;
};

