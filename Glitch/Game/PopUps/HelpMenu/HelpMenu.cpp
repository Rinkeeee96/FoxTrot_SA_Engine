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
			Text text(textId--, 
				new ColoredText(command.second,
					Color(0, 0, 0), 
					false
				),
				200, 50, WINDOW_WIDTH_CENTER - 100, WINDOW_HEIGHT - (helpCommandStartOffset + 50)
			);

			PrimaryButton keycodeBtn{ buttonId--, "command.first",[]() {}, this->dispatcher }
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