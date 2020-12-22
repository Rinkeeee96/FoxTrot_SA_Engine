#pragma once
#include "Game/General/KeyCodeStringMap.h"
#include "Game/PopUps/IPopup.h"

/// @brief Class for the Helpscreen PopUp.
class HelpMenu : public IPopup
{
public:
	HelpMenu(unique_ptr<Engine>& _engine, EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine) :
		IPopup(_engine, _dispatcher, _stateMachine) {};
	~HelpMenu() {};
	// Inherited via IPopup
	void setupPopUp() override;
	void cleanPopUp() override;
	void onAttach() override;
	void onDetach() override;

private:
	void parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header);

	float helpCommandStartOffset = 250;
	int textId = -1;
};