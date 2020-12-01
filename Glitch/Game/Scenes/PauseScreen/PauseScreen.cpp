#include "pch.h"
#include "PauseScreen.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

PauseScreen::PauseScreen()
{
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

void PauseScreen::onDetach()
{
}

void PauseScreen::start()
{
}

void PauseScreen::onUpdate()
{

}

void PauseScreen::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-1010, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-1011, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-1012, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(14);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
}

void PauseScreen::loadMusic()
{
}

void PauseScreen::loadButtons()
{
}
