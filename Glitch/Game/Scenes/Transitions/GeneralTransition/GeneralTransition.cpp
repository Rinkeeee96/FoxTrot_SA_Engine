#include "pch.h"
#include "GeneralTransition.h"
#include "Game/SpriteState.h"
#include "Game/Game.h"

/// @brief 
/// Loads the background and sets the starttime of this scene;
void GeneralTransition::onAttach()
{
	loadBackground();
	startTime = chrono::high_resolution_clock::now();
	previousCallTime = chrono::high_resolution_clock::now();
	moveCharacter = false;
}

/// @brief 
void GeneralTransition::onDetach()
{

}

/// @brief 
void GeneralTransition::start(bool playSound)
{

}

/// @brief 
/// Loads all the sprites 
void GeneralTransition::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-500, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-501, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-502, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");
	SpriteObject* PROGRESSBAR_EMPTY = new SpriteObject(-503, 24, 192, 1, 1, "Assets/LoadingBar/progress-bar-empty.png");
	SpriteObject* PROGRESSBAR_FULL = new SpriteObject(-504, 24, 192, 1, 1, "Assets/LoadingBar/progress-bar-full.png");

	auto* layer0 = new Drawable(-505);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* progressBar = new Drawable(-506);
	progressBar->setStatic(true);
	progressBar->setPositionX(585);
	progressBar->setPositionY(950);
	progressBar->setWidth(750);
	progressBar->setHeight(100);
	progressBar->registerSprite(SpriteState::DEFAULT, PROGRESSBAR_EMPTY);
	progressBar->changeToState(SpriteState::DEFAULT);

	progressBarFiller = new Drawable(-507);
	progressBarFiller->setStatic(true);
	progressBarFiller->setPositionX(616);
	progressBarFiller->setPositionY(921);
	progressBarFiller->setWidth(10);
	progressBarFiller->setHeight(42);
	progressBarFiller->registerSprite(SpriteState::DEFAULT, PROGRESSBAR_FULL);
	progressBarFiller->changeToState(SpriteState::DEFAULT);

	animation = new Drawable(-508);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(-509);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, layer2, false, true);
	addNewObjectToLayer(3, progressBar);
	addNewObjectToLayer(4, progressBarFiller);
}

/// @brief 
/// Runs the scene.
/// Calculates every 0.5s and random nr between 1 and 150 to increase the loading bar with. 
/// Also sets the loading bar. 
void GeneralTransition::onUpdate()
{
	
	chrono::duration<double> diffFromPreviousCall = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - previousCallTime);

	if (diffFromPreviousCall.count() > 0.5 && !moveCharacter)
	{
		if (progressBarFiller->getWidth() >= 685)
		{
			moveCharacter = true;
			return;
		}


		int generated = rand() % 685 + 1;
		if (progressBarFiller->getWidth() + generated > 685)
		{
			progressBarFiller->setWidth(685);
			return;
		}
		else
		{
			progressBarFiller->setWidth(progressBarFiller->getWidth() + generated);
		}
		previousCallTime = chrono::high_resolution_clock::now();
	}

	if (diffFromPreviousCall.count() > 0.05 && moveCharacter)
	{
		animation->setPositionX(animation->getPositionX() + 20);
		previousCallTime = chrono::high_resolution_clock::now();
		if (animation->getPositionX() > WINDOW_WIDTH)
		{
			stateMachine.switchToScene(nextScene,false);
		}
		
	}
}

void GeneralTransition::setNextScene(string const identifier)
{
	nextScene = identifier;
}
