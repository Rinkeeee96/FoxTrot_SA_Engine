#include "pch.h"
#include "HelpMenu.h"


void HelpMenu::setupPopUp()
{
	shared_ptr<SpriteObject> backgroundSprite = shared_ptr<SpriteObject>(new SpriteObject(-564577, 300, 500, 1, 1, "Assets/Sprites/PopUp/PopUpText-300x500.png"));
	shared_ptr<Drawable> background = shared_ptr<Drawable>(new Drawable(-564574));
	background->setHeight(700);
	background->setWidth(500);
	background->setDrawStatic(true);

	background->setPositionX(WINDOW_WIDTH_CENTER - 250);
	background->setPositionY(WINDOW_HEIGHT_CENTER + 300);

	background->registerSprite(SpriteState::DEFAULT, backgroundSprite);
	background->changeToState(SpriteState::DEFAULT);
	addObjectInLayer(background);

	auto invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	if (invoker)
	{
		parseKeycodeList(invoker->getPlayerCommands(), "player controls");
		helpCommandStartOffset += 60;
		parseKeycodeList(invoker->getGlobalCommands(), "misc and global commands");
	}
}

void HelpMenu::parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header) {
	// set the header for the section
	shared_ptr<Text> text = shared_ptr<Text>(
		new Text(textId--,
			new ColoredText(header,
				Color(0, 0, 0),
				false
			),
			250.f, 80.f, WINDOW_WIDTH_CENTER - 120.f, (helpCommandStartOffset += 50.f))
	);
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
			50.f, 50.f, WINDOW_WIDTH_CENTER - 120.f, (helpCommandStartOffset += 50.f)
		));
		// TODO make this a description (prob in json as attribute?) for now this works
		shared_ptr<Text> description = shared_ptr<Text>(new Text(textId--,
			new ColoredText(identifier,
				Color(0, 0, 0),
				false
			),
			200.f, 50.f, WINDOW_WIDTH_CENTER - 50.f, helpCommandStartOffset)
		);

		addObjectInLayer(keycodeString);
		addObjectInLayer(description);
	};
}

void HelpMenu::cleanPopUp()
{
	textId = -1;
	helpCommandStartOffset = 250;
	this->clearObjects();
}

void HelpMenu::onAttach()
{
	TogglePauseEvent pauseEvent(true);
	dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	setAlwaysVisible(true);

	this->setupPopUp();
}

void HelpMenu::onDetach()
{
	TogglePauseEvent pauseEvent(false);
	dispatcher.dispatchEvent<TogglePauseEvent>(pauseEvent);
	setAlwaysVisible(false);

	this->cleanPopUp();
}