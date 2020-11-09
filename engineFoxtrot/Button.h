#pragma once
#include "SceneManager/Object.h"
#include "Structs/Color.h"
class Button : public Object
{
public:
	Button(int id, string _text, Color _color) : 
		Object(id), color(_color), text(_text) {}
	~Button();

	const string& getText() { return text; }
	const Color& getColor() { return color; }

	void updateText(string updatedText) { text = updatedText; }

	void onClick() {}

private:
	Color color;
	string text;
};

