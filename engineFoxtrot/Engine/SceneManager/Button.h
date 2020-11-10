#pragma once
#include "Events/EventSingleton.h"
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"
#include "Structs/HelperStructs.h"
#include <any>

class API Button : public Drawable
{
public:
	Button(int id, ColoredString _text, const function<void(void)> _onClick) :
		Drawable(id), 
		text(_text),
		onClick(_onClick)
	{
		setStatic(true);
		isMouseOver = true;
		EventSingleton::get_instance().setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
		EventSingleton::get_instance().setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
	}

	const ColoredString& getText() { return text; }

	void disable() { isEnabled = false; }
	void enable() { isEnabled = true; }

	void setSize(int width, int height) {
		setWidth(width);
		setHeight(height);
	}

	void mouseOver(Event& event);
	void isClicked(Event& event);

	// TODO	 https://stackoverflow.com/questions/26208918/vector-that-can-have-3-different-data-types-c
	vector<std::any> draw() override {
		return {
			text,
			currentSprite
		};
	}

private:
	bool isEnabled = true;
	bool isMouseOver = false;
	void onMouseOver();

	const function<void(void)> onClick;

	ColoredString text;
};

