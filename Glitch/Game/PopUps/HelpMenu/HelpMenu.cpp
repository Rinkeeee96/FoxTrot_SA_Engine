#include "pch.h"
#include "HelpMenu.h"


void HelpMenu::setupPopUp()
{
	auto invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	if (invoker)
	{
		parseKeycodeList(invoker->getPlayerCommands(), "player controls");
		parseKeycodeList(invoker->getGlobalCommands(), "misc and global commands");
	}
}

void HelpMenu::parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header) {
	int textId = -1;
	// set a large enough offset so the id's won't overlap......
	int buttonId = -900;
	int helpCommandStartOffset = 300;
	// set the header for the section
	addObjectInLayer(shared_ptr<Text>(
	new Text(textId,
		new ColoredText(header,
			Color(0, 0, 0),
			false
		),
		250, 80, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT - (helpCommandStartOffset + 50)
		)
	));
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
			80, 20, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT - (helpCommandStartOffset + 50)
		));
		// TODO make this a description (prob in json as attribute?) for now this works
		shared_ptr<Text> description = shared_ptr<Text>(new Text(textId--,
			new ColoredText(identifier,
				Color(0, 0, 0),
				false
			),
			200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT - (helpCommandStartOffset * 2 + 50)
		));

		addObjectInLayer(keycodeString);
		addObjectInLayer(description);
	};
}

void HelpMenu::cleanPopUp()
{
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