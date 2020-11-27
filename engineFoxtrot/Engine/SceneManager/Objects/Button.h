#pragma once
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"

#define DEFAULT_SPRITEID		1
#define HOVER_SPRITEID			2

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

		int defaultSpriteId = DEFAULT_SPRITEID;

		registerSprite(defaultSpriteId, _spriteObject);
		changeToState(defaultSpriteId);

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

	API void registerHoverSprite(SpriteObject* spriteObject);
private:
	bool isEnabled = true;
	bool isMouseOver = false;
	bool buttonPressed = false;
	bool hasHoverSprite = false;

	const function<void(void)> onClick;

	ColoredText text;
};


