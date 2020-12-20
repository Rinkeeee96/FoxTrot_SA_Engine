#include "pch.h"
#include "HelpMenu.h"


void HelpMenu::setupPopUp()
{
	auto invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	if (invoker)
	{
		int textId = -1;
		// set a large enough offset so the id's won't overlap......
		int buttonId = -900;
		int helpCommandStartOffset = 300;

		for (pair<KeyCode, string> command : invoker->getPlayerCommands())
		{
			const KeyCode& keyCode = command.first;
			const string& identifier = command.second;

			Text keycodeString(textId--, 
				new ColoredText(keycodeStringMap[keyCode],
					Color(0, 0, 0), 
					false
				),
				200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT - (helpCommandStartOffset + 50)
			);
			// TODO make this a description (prob in json as attribute?)
			Text description(textId--,
				new ColoredText(keycodeStringMap[keyCode],
					Color(0, 0, 0),
					false
				),
				200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT - (helpCommandStartOffset + 50)
			);
			
		};
	}


}

void HelpMenu::cleanPopUp()
{
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