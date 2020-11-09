#pragma once
#include "SceneManager/Object.h"
#include "Structs/Color.h"
#include "Events/Mouse/MousePressed.h"
#include "Events/EventSingleton.h"

class Button : public Object
{
public:
	Button(int id, string _text, Color _color) :
		Object(id), color(_color), text(_text)
	{
		EventSingleton::get_instance().setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(isClicked));
	
	}
	~Button();

	const string& getText() { return text; }
	const Color& getColor() { return color; }

	void updateText(string updatedText) { text = updatedText; }

	void disable() { isEnabled = false; }
	void enable() { isEnabled = true; }

	void setSize(int width, int height) {
		setWidth(width);
		setHeight(height);
	}

	void mouseOver(Event& event) {
		auto mouseOverEvent = static_cast<MouseMovedEvent&>(event);
		int x = mouseOverEvent.GetX();
		int y = mouseOverEvent.GetY();
		
		// TODO check if mouse is in bounds
		
	}

	void isClicked(Event& event) {
		auto mousePressedEvent = static_cast<MouseButtonPressed&>(event);

		if (isMouseOver && isEnabled)
		{

		}

	}
private:
	bool isEnabled = true;
	bool isMouseOver = false;

	Color color;
	string text;
};

