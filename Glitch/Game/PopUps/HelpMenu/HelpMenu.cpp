#include "pch.h"
#include "HelpMenu.h"
#include "Game/General/KeyCodeStringMap.h"

/// @brief The setup function to create the Pop up layer
void HelpMenu::setupPopUp()
{
	shared_ptr<SpriteObject> backgroundSprite = shared_ptr<SpriteObject>(new SpriteObject(-564577, 300, 500, 1, 1, "Assets/Sprites/PopUp/PopUpText-300x500.png"));
	shared_ptr<Drawable> background = shared_ptr<Drawable>(new Drawable(-564574));
	background->setHeight(800);
	background->setWidth(1000);
	background->setDrawStatic(true);

	background->setPositionX(WINDOW_WIDTH_CENTER - 500);
	background->setPositionY(WINDOW_HEIGHT_CENTER + 400);

	background->registerSprite(SpriteState::DEFAULT, backgroundSprite);
	background->changeToState(SpriteState::DEFAULT);
	addObjectInLayer(background);

	auto invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	if (invoker)
	{
		parseKeycodeList(invoker->getPlayerCommands(), "Player controls");
		helpCommandStartOffset += 80;
		parseKeycodeList(invoker->getGlobalCommands(), "Misc and global commands");
	}
}

/// @brief Function that creates text functions from the set keycode's
/// @param parseList 
/// @param header 
void HelpMenu::parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header) {
	// set the header for the section
	shared_ptr<Text> text = shared_ptr<Text>(
		new Text(textId--,
			new ColoredText(header,
				Color(130, 41, 18),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * header.length(), 70.f, WINDOW_WIDTH_CENTER - 450.f, (helpCommandStartOffset += 50.f))
	);
	text->setDrawStatic(true);
	addObjectInLayer(text);

	// parse and add the keycodes to the screen
	for (pair<KeyCode, string> command : parseList)
	{
		const KeyCode& keyCode = command.first;
		const string& identifier = command.second;

		shared_ptr<Text> keycodeString = shared_ptr<Text>(new Text(textId--,
			new ColoredText(keycodeStringMap[keyCode],
				Color(0, 0, 0),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, WINDOW_WIDTH_CENTER - 450.f, (helpCommandStartOffset += 50.f)
		));
		// TODO make this a description (prob in json as attribute?) for now this works
		shared_ptr<Text> description = shared_ptr<Text>(new Text(textId--,
			new ColoredText(identifier,
				Color(0, 0, 0),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * identifier.length(), 50.f, WINDOW_WIDTH_CENTER - 380.f, helpCommandStartOffset)
		);

		description->setDrawStatic(true);
		keycodeString->setDrawStatic(true);

		addObjectInLayer(keycodeString);
		addObjectInLayer(description);
	};
}

/// @brief Cleans the popUp
void HelpMenu::cleanPopUp()
{
	textId = -1;
	helpCommandStartOffset = 250;
	this->clearObjects();
}

void HelpMenu::onAttach()
{
	this->stateMachine->registerActivePopup(this);
	this->setupPopUp();
	setAlwaysVisible(true);

	if (this->stateMachine->activePopupCount() <= 1) {
		TogglePauseEvent pauseEvent(true);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	}
}

void HelpMenu::onDetach()
{
	this->stateMachine->deregisterActivePopup(this);
	this->cleanPopUp();
	setAlwaysVisible(false);

	if (this->stateMachine->activePopupCount() <= 0) {
		TogglePauseEvent pauseEvent(false);
		dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	}
}
