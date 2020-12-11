#pragma once
#include "SceneManager/Objects/Button.h"
#include "Game/SpriteState.h"

/// @brief Class for a red secondary button, derived from button base class
class SecondaryButton : public Button
{
public:
	SecondaryButton(int id, string _text, const function<void(void)> _onClick, EventDispatcher& _dispatcher) : 
		Button(id, ColoredText(_text, Color(255, 255, 255)), _onClick, new SpriteObject(101011, 40, 116, 1, 300, "Assets/Buttons/btn_red_round.png"), _dispatcher) {
	}
};