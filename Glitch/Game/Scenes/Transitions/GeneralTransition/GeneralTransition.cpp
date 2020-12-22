#include "pch.h"
#include "GeneralTransition.h"
#include "Game/SpriteState.h"
#include "Game/Game.h"

/// @brief 
/// Loads the background and sets the starttime of this scene;
void GeneralTransition::onAttach()
{
	loadBackground();
}

/// @brief 
void GeneralTransition::onDetach(){}

/// @brief 
void GeneralTransition::start(bool playSound){}

/// @brief 
/// Loads all the sprites 
void GeneralTransition::loadBackground()
{
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-500, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png"));
	shared_ptr<SpriteObject> BG_LAYER_ADVENTRUE = shared_ptr<SpriteObject>(new SpriteObject(-501, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png"));
	shared_ptr<SpriteObject> BG_LAYER_2 = shared_ptr<SpriteObject>(new SpriteObject(-502, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png"));
	shared_ptr<SpriteObject> LOGO = shared_ptr<SpriteObject>(new SpriteObject(-503, 185, 606, 1, 300, "Assets/Advertisments/Avans_Hogeschool_Logo.png"));
	shared_ptr<SpriteObject> ADVERTISMENT_BLOCK = shared_ptr<SpriteObject>(new SpriteObject(-504, 309, 253, 1, 300, "Assets/Inventory/text_background.png"));

	shared_ptr<Drawable> layer0 = shared_ptr<Drawable>(new Drawable(-505));
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	animation = shared_ptr<Drawable>(new Drawable(-506));
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	shared_ptr<Drawable> layer2 = shared_ptr<Drawable>(new Drawable(-507));
	layer2->setStatic(true);
	layer2->setPositionX(0);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> adBlcok = shared_ptr<Drawable>(new Drawable(-508));
	adBlcok->setStatic(true);
	adBlcok->setPositionX(1380);
	adBlcok->setPositionY(1055);
	adBlcok->setWidth(505);
	adBlcok->setHeight(180);
	adBlcok->registerSprite(SpriteState::DEFAULT, ADVERTISMENT_BLOCK);
	adBlcok->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> ad = shared_ptr<Drawable>(new Drawable(-509));
	ad->setStatic(true);
	ad->setPositionX(1420);
	ad->setPositionY(1040);
	ad->setWidth(431);
	ad->setHeight(127);
	ad->registerSprite(SpriteState::DEFAULT, LOGO);
	ad->changeToState(SpriteState::DEFAULT);

	shared_ptr<Text> advertisment = shared_ptr<Text>(new Text(-510, new ColoredText("Advertisement:", Color(0, 0, 0)), 120, 30, 1420, 895));
	
	
	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, layer2, false, true);
	addNewObjectToLayer(3, adBlcok, false, true);
	addNewObjectToLayer(4, ad, false, true);
	addNewObjectToLayer(4, advertisment, false, true);
}

/// @brief 
/// Runs the scene.
/// Calculates every 0.5s and random nr between 1 and 150 to increase the loading bar with. 
/// Also sets the loading bar. 
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void GeneralTransition::onUpdate(float deltaTime)
{
	timer += deltaTime;

	animation->setPositionX(animation->getPositionX() + (600 * deltaTime));
	if (animation->getPositionX() > WINDOW_WIDTH)
	{
		stateMachine->switchToScene(nextScene,false);
	}
}

/// @brief Sets the next scene identifier
/// @param identifier 
void GeneralTransition::setNextScene(string const identifier)
{
	nextScene = identifier;
}
