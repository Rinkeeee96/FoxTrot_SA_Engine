#include "pch.h"
#include "MainScene.h"

void MainScene::loadScene()
{
	Drawable* groundObject = new Drawable(1, false);
	SpriteObject* groundSprite = new SpriteObject(1, 32, 32, 1, 10, "Assets/ground.png");

	SpriteObject* characterRunRightSprite = new SpriteObject(2, 34, 32, 14, 100, "Assets/character_run_right.png");
	SpriteObject* characterRunLeftSprite = new SpriteObject(3, 34, 32, 14, 100, "Assets/character_run_left.png");

	SpriteObject* characterIdleRightSprite = new SpriteObject(4, 34, 32, 13, 100, "Assets/character_idle_right.png");
	SpriteObject* characterIdleLeftSprite = new SpriteObject(5, 34, 32, 13, 100, "Assets/character_idle_left.png");

	DynamicObject* dynamicObject = new DynamicObject(5, this->getEventDispatcher());

	groundObject->setPositionX(25);
	groundObject->setPositionY(900);
	groundObject->setWidth(1500);
	groundObject->setHeight(50);
	groundObject->setStatic(true);
	groundObject->registerSprite(1, groundSprite);
	groundObject->changeToState(1);

	dynamicObject->setPositionX(200);
	dynamicObject->setPositionY(500);
	dynamicObject->setWidth(50);
	dynamicObject->setHeight(50);
	dynamicObject->setStatic(false);
	dynamicObject->registerSprite(SpriteState::IDLE_RIGHT, characterIdleRightSprite);
	dynamicObject->registerSprite(SpriteState::IDLE_LEFT, characterIdleLeftSprite);
	dynamicObject->registerSprite(SpriteState::RUN_RIGHT, characterRunRightSprite);
	dynamicObject->registerSprite(SpriteState::RUN_LEFT, characterRunLeftSprite);
	dynamicObject->changeToState(SpriteState::IDLE_RIGHT);
	dynamicObject->setScale(3);
	
	addNewObjectToLayer(2, groundObject, true, false);
	addNewObjectToLayer(4, dynamicObject, true, true);

	this->setObjectToFollow(dynamicObject);
}

void MainScene::onAttach()
{
	loadScene();
	engine.soundEngine.onLoadBackgroundMusicEvent("APPLAUSE", "Assets/applause.wav");
}

void MainScene::onDetach()
{
}

void MainScene::start(bool playSound)
{
	if (playSound)engine.soundEngine.onStartBackgroundMusicEvent("APPLAUSE");
}

void MainScene::onUpdate()
{
}
