#pragma once
#include "SceneManager/Objects/Button.h"
#include "Game/SpriteState.h"

class SecondaryButton : public Button
{
public:
	SecondaryButton(int id, string _text, const function<void(void)> _onClick) : Button(id, ColoredText(_text, Color(255, 255, 255)), _onClick) {
		auto mainSprite = new SpriteObject(101011, 40, 116, 1, 300, "Assets/Buttons/btn_red_round.png");
		setSize(200, 50);
		registerSprite(SpriteState::DEFAULT, mainSprite);
		changeToState(SpriteState::DEFAULT);
	}
	~SecondaryButton() {
		// TODO refactor sprite pointer to enforce ownership
		delete currentSprite;
	};

private:

};