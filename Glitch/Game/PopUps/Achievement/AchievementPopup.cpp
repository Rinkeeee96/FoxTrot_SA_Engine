#include "pch.h"
#include "AchievementPopup.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/SpriteState.h"

#define BIND_FN(function) std::bind(&AchievementPopup::function, *this)

AchievementPopup::AchievementPopup(EventDispatcher& _dispatcher, SceneStateMachine& _stateMachine) :
	dispatcher(_dispatcher), stateMachine(_stateMachine)
{
	setAlwaysVisible(true);
}

AchievementPopup::~AchievementPopup()
{
}

/// @brief Setup the Pause Pop Up.
void AchievementPopup::setupPopUp(string& achievement)
{
	SpriteObject* backgroundSprite = new SpriteObject(-12001, 200, 500, 1, 1, "Assets/Sprites/PopUp/PopUpGreenBorder.png");

	Text* text = new Text(-12003, new ColoredText(achievement, Color(0, 0, 0), false),200, 50, WINDOW_WIDTH_CENTER - 220,200);
	text->setDrawStatic(true);

	Drawable* background = new Drawable(-12000);
	background->setHeight(150);
	background->setWidth(500);
	background->setDrawStatic(true);
	background->setPositionX(WINDOW_WIDTH_CENTER - 250);
	background->setPositionY(200);
	background->registerSprite(SpriteState::DEFAULT, backgroundSprite);
	background->changeToState(SpriteState::DEFAULT);

	addObjectInLayer(text);

	addObjectInLayer(background);

}