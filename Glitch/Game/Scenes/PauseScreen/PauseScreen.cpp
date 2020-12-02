#include "pch.h"
#include "PauseScreen.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&PauseScreen::function, *this)

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

void PauseScreen::loadButtons()
{

	//// Resume button
	auto* resumeButton = new PrimaryButton(10, "Resume", BIND_FN(onResumeButtonClick));
	resumeButton->setPositionX(CENTER_X - (resumeButton->getWidth() / 2));
	resumeButton->setPositionY(CENTER_Y - 100);

	// Exit button
	auto* exitButton = new PrimaryButton(11, "Exit Level", BIND_FN(onExitButtonClick));
	exitButton->setPositionX(CENTER_X - (exitButton->getWidth() / 2));
	exitButton->setPositionY(CENTER_Y - 40);

	// Music on/off button
	auto* musicButton = new PrimaryButton(12, "Music On/Off", BIND_FN(onMusicButtonClick));
	musicButton->setPositionX(CENTER_X - (musicButton->getWidth() / 2));
	musicButton->setPositionY(CENTER_Y + 20);

	// Help button
	auto* helpButton = new PrimaryButton(13, "Help", BIND_FN(onHelpButtonClick));
	helpButton->setPositionX(CENTER_X - (helpButton->getWidth() / 2));
	helpButton->setPositionY(CENTER_Y + 80);

	addNewObjectToLayer(3, resumeButton);
	addNewObjectToLayer(3, exitButton);
	addNewObjectToLayer(3, musicButton);
	addNewObjectToLayer(3, helpButton);
}

void PauseScreen::loadMusic()
{
}

void PauseScreen::onResumeButtonClick()
{
	stateMachine->switchToScene(stateMachine->getCurrentSceneIdentifier(), false);
}

void PauseScreen::onExitButtonClick()
{
	stateMachine->switchToScene("Overworld", false);
}

void PauseScreen::onMusicButtonClick()
{
}

void PauseScreen::onHelpButtonClick()
{
}

