#include "pch.h"
#include "PausePopUp.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/SpriteState.h"

#define BIND_FN(function) std::bind(&PausePopUp::function, *this)

PausePopUp::PausePopUp(EventDispatcher &_dispatcher, SceneStateMachine& _stateMachine) : 
	dispatcher(_dispatcher), stateMachine(_stateMachine)
{
}

PausePopUp::~PausePopUp()
{
}

/// @brief Setup the Pause Pop Up.
void PausePopUp::setupPopUp()
{
	Drawable* background = new Drawable(-564574);
	SpriteObject* backgroundSprite = new SpriteObject(-564577, 200, 500, 1, 1, "Assets/Sprites/PopUp/PopUpBlackBorder.png");
	Text* text = new Text(	-564573, new ColoredText("Paused", Color(0,0,0), false), 
							200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT_CENTER - 175);

	PrimaryButton *backButton = new PrimaryButton(-564572, "Back to Overworld", BIND_FN(onBackButtonClick), dispatcher);
	backButton->setHeight(50);
	backButton->setWidth(200);
	backButton->setPositionX(WINDOW_WIDTH_CENTER - 100);
	backButton->setPositionY(WINDOW_HEIGHT_CENTER - 100);
	backButton->setDrawStatic(true);

	background->setHeight(300);
	background->setWidth(500);
	background->setDrawStatic(true);

	background->setPositionX(WINDOW_WIDTH_CENTER - 250);
	background->setPositionY(WINDOW_HEIGHT_CENTER);

	background->registerSprite(SpriteState::DEFAULT, backgroundSprite);
	background->changeToState(SpriteState::DEFAULT);

	text->setDrawStatic(true);
	addObjectInLayer(backButton);
	addObjectInLayer(text);
	addObjectInLayer(background);
}

void PausePopUp::onBackButtonClick()
{
	stateMachine.switchToScene("Overworld", false);
}
