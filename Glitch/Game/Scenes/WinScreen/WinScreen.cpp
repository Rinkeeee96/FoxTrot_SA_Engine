#include "pch.h"
#include "WinScreen.h"
#include "stdafx.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&WinScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void WinScreen::onAttach()
{
	LoadButtons();
	LoadBackground();
	LoadMusic();
}

/// @brief 
/// Create all buttons for this scene
void WinScreen::LoadButtons() {
	auto mainSprite = new SpriteObject(-602, 40, 116, 1, 300, "Assets/Buttons/btn_gray_round.png");

	auto* overBtn = new Button(-700, ColoredText("Overworld", Color(0, 0, 0)), BIND_FN(onOverworldBtnClick), mainSprite, this->dispatcher);
	overBtn->setPositionX(CENTER_X - overBtn->getWidth() / 2);
	overBtn->setPositionY(CENTER_Y - overBtn->getHeight() / 2);

	auto* mainBtn = new Button(-701, ColoredText("Hoofdmenu", Color(0, 0, 0)), BIND_FN(OnMainBtnClick), mainSprite, this->dispatcher);
	mainBtn->setPositionX(CENTER_X - mainBtn->getWidth() / 2);
	mainBtn->setPositionY(CENTER_Y - mainBtn->getHeight() / 2 + 200);

	addNewObjectToLayer(3, overBtn);
	addNewObjectToLayer(3, mainBtn);
}

/// @brief 
/// Create the background for this scene
void WinScreen::LoadBackground() {
	SpriteObject* BG_LAYER_0 = new SpriteObject(-992882, 1080, 1920, 1, 300, "Assets/Backgrounds/game_win_layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE_JUMP = new SpriteObject(-992883, 37, 50, 2, 300, "Assets/Sprites/Character/adventurer_jump_straight.png");
	SpriteObject* BG_LAYER_ADVENTRUE_FALL = new SpriteObject(-992884, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-992885, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* particleSprite = new SpriteObject(-992886, 20, 20, 20, 300, "Assets/Particles/fire.png");


	auto* layer0 = new Drawable(34);
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	animation = new Drawable(35);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(1030);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE_JUMP);
	animation->registerSprite(SpriteState::AIR_JUMP_RIGHT, BG_LAYER_ADVENTRUE_JUMP);
	animation->registerSprite(SpriteState::AIR_FALL_RIGHT, BG_LAYER_ADVENTRUE_FALL);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	ParticleAdapter* confetti = new ParticleAdapter(11);        
	confetti->registerSprite(SpriteState::DEFAULT, particleSprite);
	confetti->changeToState(SpriteState::DEFAULT);
	confetti->setPositionX(CENTER_X);
	confetti->setPositionY(CENTER_Y);
	confetti->setStyle(ParticleInit::ParticleStyle::EXPLOSION);
	confetti->setStartSpin(0);
	confetti->setStartSpinVar(90);
	confetti->setEndSpin(90);
	confetti->setStartSpinVar(90);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, confetti, false, true);
}

/// @brief 
/// Load the sounds for this scene
void WinScreen::LoadMusic() {

	engine.loadSound("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav");
}


/// @brief 
/// Create the sounds for this scene
void WinScreen::start(bool playSound)
{
	if(playSound)engine.startSound("WIN_SOUND");
}

void WinScreen::onDetach()
{
	Scene::onDetach();
}

/// @brief 
/// Remove the sounds of the soundengine
void WinScreen::OnMainBtnClick()
{
	stateMachine.switchToScene("MainMenu", false);
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworld
void WinScreen::onOverworldBtnClick() {
	stateMachine.switchToScene("Overworld", false);
}

/// @brief 
/// A function for a jump/fall animation
void WinScreen::onUpdate(float deltaTime) {
	if (animation->getPositionY() < 800) {
		animation->changeToState(SpriteState::AIR_FALL_RIGHT);
		falling = true;
	}
	else if (animation->getPositionY() > 1080) {
		animation->changeToState(SpriteState::AIR_JUMP_RIGHT);
		falling = false;
	}
	
	if (falling) {
		animation->setPositionY(animation->getPositionY() + deltaTime * 300);
	}
	else {
		animation->setPositionY(animation->getPositionY() - deltaTime * 300);
	}
}