#pragma once
#include "SceneManager/Objects/Button.h"
#include "Game/SpriteState.h"

class SecondaryButton : public Button
{
public:
	SecondaryButton(int id, string _text, const function<void(void)> _onClick,const EventDispatcher& _dispatcher) : 
		Button(id, ColoredText(_text, Color(255, 255, 255)), _onClick, new SpriteObject(101011, 40, 116, 1, 300, "Assets/Buttons/btn_red_round.png"), _dispatcher) {
	}
};