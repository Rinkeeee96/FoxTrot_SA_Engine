#pragma once
#include "SceneManager/Button.h"
#include "../SpriteState.h"
class PrimaryButton : public Button
{
public:
	PrimaryButton(int id, string _text, const function<void(void)> _onClick) : Button(id, ColoredString(_text, Color(0,0,0)), _onClick) {
		auto mainSprite = new SpriteObject(101010, 40, 116, 1, 300, "Assets/Buttons/btn_green_round.png");	
		setSize(200, 50); 
		registerSprite(SpriteState::DEFAULT, mainSprite);
		changeToState(SpriteState::DEFAULT);
	}
	~PrimaryButton() {
		// TODO refactor sprite pointer to enforce ownership
		delete currentSprite;
	};

private:

};