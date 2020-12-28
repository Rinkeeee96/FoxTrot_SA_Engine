#include "pch.h"
#include "AchievementPopup.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/SpriteState.h"

#define BIND_FN(function) std::bind(&AchievementPopup::function, *this)

AchievementPopup::AchievementPopup(EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine) :
	dispatcher(_dispatcher), stateMachine(_stateMachine)
{
	setAlwaysVisible(true);
}

AchievementPopup::~AchievementPopup()
{
}

/// @brief Setup the Achievement popup
/// @param achievement 
void AchievementPopup::setupPopUp(Achievement& achievement)
{
	shared_ptr<SpriteObject> backgroundSprite = shared_ptr<SpriteObject>(new SpriteObject(-564577, 300, 500, 1, 1, "Assets/Sprites/PopUp/PopUpText-300x500.png"));
	shared_ptr<Text> text = shared_ptr<Text>(new Text(-564573, new ColoredText(achievement, Color(0, 0, 0), false),200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT_CENTER - 395));
	text->setDrawStatic(true);

	shared_ptr<Drawable> background = shared_ptr<Drawable>(new Drawable(-564574));
	background->setHeight(120);
	background->setWidth(500);
	background->setDrawStatic(true);
	background->setPositionX(WINDOW_WIDTH_CENTER - 250);
	background->setPositionY(WINDOW_HEIGHT_CENTER - 350);
	background->registerSprite(SpriteState::DEFAULT, backgroundSprite);
	background->changeToState(SpriteState::DEFAULT);

	addObjectInLayer(text);
	addObjectInLayer(background);
}