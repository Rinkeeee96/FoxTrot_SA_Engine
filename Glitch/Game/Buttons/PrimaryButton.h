#pragma once
#include "SceneManager/Objects/Button.h"
#include "Game/SpriteState.h"

class PrimaryButton : public Button
{
public:
	PrimaryButton(int id, string _text, const function<void(void)> _onClick, EventDispatcher& _dispatcher) : 
		Button(id, ColoredText(_text, Color(0,0,0)), _onClick, new SpriteObject(101010, 40, 116, 1, 300, "Assets/Buttons/btn_green_round.png"), _dispatcher) {
		auto hoverPrimaryBtn = new SpriteObject(101020, 40, 116, 1, 300, "Assets/Buttons/btn_brown_round.png");
		hasHoverSprite = true;
		Drawable::registerSprite(HOVER_STATE, hoverPrimaryBtn);
	}
};