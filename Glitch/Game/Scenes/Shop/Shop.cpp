#include "pch.h"
#include "Shop.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&Shop::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void Shop::onAttach()
{

	loadButtons();
	loadBackground();
	loadMusic();

}

void Shop::onDetach()
{
	Scene::onDetach();
}

void Shop::start(bool playSound)
{
	if (playSound)engine.startSound("MENU_SOUND");
}

void Shop::onUpdate()
{
}

void Shop::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-1500, 1080, 1920, 1, 0, "Assets/Shop/Shop.png");
	SpriteObject* ShopKeeper = new SpriteObject(-1501, 888, 924, 1, 0, "Assets/Shop/Shopkeeper.png");

	auto* layer0 = new Drawable(-992);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* keeper = new Drawable(-993);
	keeper->setStatic(true);
	keeper->setPositionX(50);
	keeper->setPositionY(1200);
	keeper->setWidth(900);
	keeper->setHeight(1000);
	keeper->registerSprite(SpriteState::DEFAULT, ShopKeeper);
	keeper->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, keeper, false, true);
}

void Shop::loadMusic()
{
	engine.loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

void Shop::loadButtons()
{
	auto* stopBtn = new SecondaryButton(-993, "To Overworld", BIND_FN(onStopBtnClick), this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, stopBtn);
}

void Shop::onStopBtnClick() {
	stateMachine.switchToScene("Overworld", false);
}