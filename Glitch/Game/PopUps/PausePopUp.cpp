#include "pch.h"
#include "PausePopUp.h"

PausePopUp::PausePopUp()
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



	background->setHeight(200);
	background->setWidth(500);

	background->setPositionX(WINDOW_WIDTH_CENTER - 250);
	background->setPositionY(WINDOW_HEIGHT_CENTER - 100);

	background->registerSprite(1 ,backgroundSprite);
	background->changeToState(1);

	addObjectInLayer(text->getObjectId(), text);
	addObjectInLayer(background->getObjectId(), background);
}
