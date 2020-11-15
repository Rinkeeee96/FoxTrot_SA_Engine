#include "MainMenuTransitionToGame.h"
#include "../../SpriteState.h"

void MainMenuTransitionToGame::OnAttach()
{
	LoadBackground();
	startTime = chrono::high_resolution_clock::now();
	previousCallTime = chrono::high_resolution_clock::now();

	SpriteObject* BG_LAYER_0 = new SpriteObject(1000, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(1001, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(1002, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(1);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	animation = new Drawable(2);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(3);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, layer2);
	
}

void MainMenuTransitionToGame::OnDetach()
{

}

void MainMenuTransitionToGame::Start()
{
	
}

void MainMenuTransitionToGame::LoadBackground()
{

}

void MainMenuTransitionToGame::run()
{
	
	chrono::duration<double> diff = chrono::duration_cast<chrono::duration<double>>(previousCallTime - startTime);
	chrono::duration<double> diffFromPreviousCall = chrono::duration_cast<chrono::duration<double>>(previousCallTime - chrono::high_resolution_clock::now());

	if (diffFromPreviousCall.count() < 0.2)
	{
		animation->setPositionX(animation->getPositionX() + 2);
		if (animation->getPositionX() > WINDOW_WIDTH)
		{
			SceneSwitcher::get_instance().SwitchToScene("GAME");
		}
	}

	previousCallTime = chrono::high_resolution_clock::now();	
}