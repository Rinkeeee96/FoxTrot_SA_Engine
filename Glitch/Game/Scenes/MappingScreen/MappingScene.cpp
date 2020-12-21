#include "pch.h"
#include "MappingScene.h"
#include "Game/Game.h"

void MappingScene::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

void MappingScene::onDetach()
{
	Scene::onDetach();
}

void MappingScene::start(bool playSound)
{
}

void MappingScene::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}
}

void MappingScene::loadBackground()
{
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-999, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png"));

	shared_ptr<Drawable> background = shared_ptr<Drawable>(new Drawable(-992));
	background->setStatic(true);
	background->setPositionX(0);
	background->setPositionY(1080);
	background->setWidth(1920);
	background->setHeight(1080);
	background->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	background->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, background, false, true);
}

void MappingScene::loadMusic()
{
	engine->loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

void MappingScene::loadButtons()
{


	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(-993, "To Main Menu", onStopBtnClick, this->dispatcher));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(4, stopBtn);
}

void MappingScene::loadSaveGame()
{
}