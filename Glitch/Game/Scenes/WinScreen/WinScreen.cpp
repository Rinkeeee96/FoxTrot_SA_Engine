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

	overBtn = new Button(-700, ColoredText("Overworld", Color(0, 0, 0)), BIND_FN(onOverworldBtnClick));
	overBtn->setPositionX(CENTER_X - overBtn->getWidth() / 2);
	overBtn->setPositionY(CENTER_Y - overBtn->getHeight() / 2);
	overBtn->setSize(200, 50);
	overBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	overBtn->changeToState(SpriteState::DEFAULT);

	mainBtn = new Button(-701, ColoredText("Hoofdmenu", Color(0, 0, 0)), BIND_FN(OnMainBtnClick));
	mainBtn->setPositionX(CENTER_X - mainBtn->getWidth() / 2);
	mainBtn->setPositionY(CENTER_Y - mainBtn->getHeight() / 2 + 200);
	mainBtn->setSize(200, 50);
	mainBtn->registerSprite(SpriteState::DEFAULT, mainSprite);
	mainBtn->changeToState(SpriteState::DEFAULT);

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
	layer0->setPositionX(1);
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

	addNewObjectToLayer(0, layer0);
	addNewObjectToLayer(1, animation);
	addNewObjectToLayer(2, confetti);
}

/// @brief 
/// Load the sounds for this scene
void WinScreen::LoadMusic() {

	//EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("APPLAUSE_SOUND", "Assets/Sound/applause.wav"));
	EventSingleton::get_instance().dispatchEvent<SoundAttachEvent>((Event&)SoundAttachEvent("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav"));
}


/// @brief 
/// Create the sounds for this scene
void WinScreen::start()
{
	overBtn->reset();
	mainBtn->reset();
	//EventSingleton::get_instance().dispatchEvent<PlaySoundEffectEvent>((Event&)PlaySoundEffectEvent("APPLAUSE_SOUND"));
	EventSingleton::get_instance().dispatchEvent<OnMusicStartEvent>((Event&)OnMusicStartEvent("WIN_SOUND"));
}

void WinScreen::onDetach()
{
	//EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("APPLAUSE_SOUND"));
	EventSingleton::get_instance().dispatchEvent<OnMusicStopEvent>((Event&)OnMusicStopEvent("WIN_SOUND"));
	Scene::onDetach();
}

/// @brief 
/// Remove the sounds of the soundengine
void WinScreen::OnMainBtnClick()
{
	game->switchToScene("MAIN_MENU", false);
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworld
void WinScreen::onOverworldBtnClick() {
	game->switchToScene("OVERWORLD", false);
}

/// @brief 
/// A function for a jump/fall animation
void WinScreen::onUpdate() {
	animationTick++;
	if (animationTick < 100) {
		animation->setPositionY(animation->getPositionY() - 1);
	}
	else if (animationTick == 100) {
		animation->changeToState(SpriteState::AIR_FALL_RIGHT);
		animation->setPositionY(animation->getPositionY() + 1);
	}
	else if (animationTick > 100 && animationTick < 200) {
		animation->setPositionY(animation->getPositionY() + 1);
	}
	else {
		animation->changeToState(SpriteState::AIR_JUMP_RIGHT);
		animationTick = 0;
	}
}