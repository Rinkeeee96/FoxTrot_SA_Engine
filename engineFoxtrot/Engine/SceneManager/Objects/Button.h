#pragma once
#include "Events\Mouse\MouseMoved.h"
#include "Events/Mouse/MousePressed.h"
#include "SceneManager/Objects/Drawable.h"

#define DEFAULT_STATE				1
#define HOVER_STATE					2

/// @brief Base class for buttons to be used in the game
class Button : public Drawable
{
public:
	API Button(int id, ColoredText _text, const function<void(void)> _onClick, shared_ptr<SpriteObject> _spriteObject,	EventDispatcher& _dispatcher);
	virtual ~Button() {};

	API const ColoredText* toString() { return &text; }

	API void disable() { isEnabled = false; }
	API void enable() { isEnabled = true; }

	API void setSize(float width, float height);

	API bool mouseOver(const Event& event);
	API bool isClicked(const Event& event);

	API void registerHoverSprite(shared_ptr<SpriteObject> spriteObject);

	/// @brief 
	/// Change the text in the button
	API void changeText(const string& newText) {
		text.text = newText;
	}
protected:
	bool hasHoverSprite = false;

private:
	bool isEnabled = true;
	bool isMouseOver = false;
	bool buttonPressed = false;

	const function<void(void)> onClick;

	EventDispatcher& dispatcher;

	ColoredText text;
};


