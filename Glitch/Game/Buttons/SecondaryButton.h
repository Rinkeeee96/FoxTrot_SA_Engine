#pragma once
#include "SceneManager/Button.h"
#include "../SpriteState.h"
class SecondaryButton : public Button
{
public:
	SecondaryButton(int id, string _text, const function<void(void)> _onClick) : Button(id, ColoredString(_text, Color(255, 255, 255)), _onClick) {
		auto mainSprite = new SpriteObject(101011, 40, 116, 1, 300, "Assets/Buttons/btn_red_round.png");
		setSize(200, 50);
		setScalable(true);
		registerSprite(SpriteState::DEFAULT, mainSprite);
		changeToState(SpriteState::DEFAULT);
	}
	~SecondaryButton() {
		// TODO refactor sprite pointer to enforce ownership
		delete currentSprite;
	};

private:

};