#include "pch.h"
#include "PausePopUp.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/SpriteState.h"
#include "Engine/Events/Action/TogglePause.h"
#include "Game/General/KeyCodeStringMap.h"

#define BIND_FN(function) std::bind(&PausePopUp::function, *this)

/// @brief Setup the Pause Pop Up.
void PausePopUp::setupPopUp()
{
	shared_ptr<Drawable> background = shared_ptr<Drawable>(new Drawable(-564574));
	shared_ptr<SpriteObject> backgroundSprite = shared_ptr<SpriteObject>(new SpriteObject(-564577,300, 500, 1, 1, "Assets/Sprites/PopUp/PopUpText-300x500.png"));
	shared_ptr<Text> text = shared_ptr<Text>(new Text(	-564573, new ColoredText("Paused", Color(0,0,0), false),
							200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT_CENTER - 175));

	KeyCode key = ((GameKeypressInvoker*)engine->getKeypressedInvoker())->getKeycodeFromIdentifier("pause");
	string sKey = keycodeStringMap[key];

	shared_ptr<Text> retText = shared_ptr<Text>(new Text(-564571, new ColoredText("Press " + sKey + " to return to game", Color(0, 0, 0), false),
		240, 50, WINDOW_WIDTH_CENTER - 120, WINDOW_HEIGHT_CENTER - 40));

	shared_ptr<PrimaryButton> backButton = shared_ptr<PrimaryButton>(new PrimaryButton(-564572, "Back to Overworld", BIND_FN(onBackButtonClick), dispatcher));
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
	retText->setDrawStatic(true);
	addObjectInLayer(backButton);
	addObjectInLayer(text);
	addObjectInLayer(background);
	addObjectInLayer(retText);
}

/// @brief Called when Back to overworld button is clicked.
void PausePopUp::onBackButtonClick()
{
	stateMachine->switchToScene("Overworld", false);
}

void PausePopUp::cleanPopUp()
{
	this->clearObjects();
}

void PausePopUp::onAttach()
{
	this->stateMachine->registerActivePopup(this);
	this->setupPopUp();
	setAlwaysVisible(true);

	if (this->stateMachine->activePopupCount() <= 1) {
		TogglePauseEvent pauseEvent(true);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	}
}

void PausePopUp::onDetach()
{
	this->stateMachine->deregisterActivePopup(this);
	this->cleanPopUp();
	setAlwaysVisible(false);

	if (this->stateMachine->activePopupCount() <= 0) {
		TogglePauseEvent pauseEvent(false);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	}
}