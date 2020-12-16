#include "pch.h"
#include "Shop.h"
#include "Game/Game.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

/// @brief 
/// Loads all buttons/backgrounds for the shop scene
void Shop::onAttach()
{

	loadButtons();
	loadBackground();
	loadMusic();

}

/// @brief 
void Shop::onDetach()
{
	Scene::onDetach();
}

/// @brief Starts the scene's sound
/// @param playSound 
void Shop::start(bool playSound)
{
	if (playSound)engine.startSound("MENU_SOUND");
}

/// @brief 
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void Shop::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine.switchToScene(nextScene, useTransition, playSound);
	}
}

/// @brief Loads the screen backGground
void Shop::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-1500, 1080, 1920, 1, 0, "Assets/Shop/Shop.png");
	SpriteObject* DialogBox = new SpriteObject(-1502, 170, 455, 1, 0, "Assets/Shop/Dialogbox1.png");

	auto* level1TextBtn = new Text(2, new ColoredText("How can i help you today?", Color(0, 0, 0)), 400, 100, 760, 865);


	auto* layer0 = new Drawable(-992);
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* dialogBox = new Drawable(-994);
	dialogBox->setStatic(true);
	dialogBox->setPositionX(800);
	dialogBox->setPositionY(950);
	dialogBox->setWidth(700);
	dialogBox->setHeight(150);
	dialogBox->registerSprite(SpriteState::DEFAULT, DialogBox);
	dialogBox->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, level1TextBtn, false, true);
	addNewObjectToLayer(1, dialogBox, false, true);
}

/// @brief Loads the music for this scene
void Shop::loadMusic()
{
	engine.loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief Loads the buttons for this scene
void Shop::loadButtons()
{
	auto* stopBtn = new SecondaryButton(-993, "To Overworld", onStopBtnClick, this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, stopBtn);
}