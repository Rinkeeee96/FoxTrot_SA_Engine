#pragma once
#include "Events/EventSingleton.h"
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"
#include "Structs/HelperStructs.h"

class API Button : public Drawable
{
public:
	Button(int id, string _text, Color _color, const function<void(void)> _onClick) :
		Drawable(id), 
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
	void onMouseOver();

	const function<void(void)> onClick;

	Color color;
	string text;
};

