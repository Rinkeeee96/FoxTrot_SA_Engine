#pragma once
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"

#define DEFAULT_STATE				1
#define HOVER_STATE					2

class Button : public Drawable
{
public:
	API Button(int id, ColoredText _text, const function<void(void)> _onClick, SpriteObject* _spriteObject) :
		Drawable(id), 
		text(_text),
		onClick(_onClick)
	{
		setSize(200, 50);
		setStatic(true);

		registerSprite(DEFAULT_STATE, _spriteObject);
		changeToState(DEFAULT_STATE);

		EventSingleton::get_instance().setEventCallback<MouseButtonPressed>(BIND_EVENT_FN(Button::isClicked));
		EventSingleton::get_instance().setEventCallback<MouseMovedEvent>(BIND_EVENT_FN(Button::mouseOver));
	}

	API virtual ~Button() override {
		cout << "desturctor BTN " << endl;
		EventSingleton::get_instance().unSubscribe<MouseMovedEvent>(BIND_EVENT_FN(Button::isClicked));
		EventSingleton::get_instance().unSubscribe<MouseButtonPressed>(BIND_EVENT_FN(Button::mouseOver));
		Drawable::~Drawable();
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

	API void registerHoverSprite(SpriteObject* spriteObject);

protected:
	bool hasHoverSprite = false;

private:
	bool isEnabled = true;
	bool isMouseOver = false;
	bool buttonPressed = false;

	const function<void(void)> onClick;

	ColoredText text;
};


