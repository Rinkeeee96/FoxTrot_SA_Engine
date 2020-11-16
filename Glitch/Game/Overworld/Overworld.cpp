#include "pch.h"
#include "Overworld.h"

#include "../Buttons/PrimaryButton.h"
#include "../Buttons/SecondaryButton.h"

#define BIND_FN(function) std::bind(&Overworld::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void Overworld::OnAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

void Overworld::LoadButtons() {

	Button* stopBtn = new SecondaryButton(2, "Stop", BIND_FN(OnStopBtnClick));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, stopBtn);
}

void Overworld::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(1010, 1440, 1344, 1, 1, "Assets/Overworld/World.png");

	auto* layer0 = new Drawable(1);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);
	layer0->setScalable(false);

	addNewObjectToLayer(0, layer0);
}
void Overworld::LoadMusic() {

}
void Overworld::Start()
{

}

void Overworld::OnDetach()
{
	Scene::OnDetach();
}

void Overworld::OnStartBtnClick()
{
	cout << "Start BTN" << endl;
}

void Overworld::OnStopBtnClick() {

}

void Overworld::OnCreditsBtnClick() {
	cout << "Start Credit" << endl;
}

void Overworld::OnLoadBtnClick() {
	cout << "Start Load game BTN" << endl;
}
