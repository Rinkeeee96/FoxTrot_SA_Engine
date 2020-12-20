#pragma once
#include "Game/PopUps/IPopup.h"
class HelpMenu : public IPopup
{
public:
	HelpMenu(EventDispatcher& _dispatcher, shared_ptr<SceneStateMachine> _stateMachine) :
		IPopup(_dispatcher, _stateMachine) {};
	~HelpMenu() {};
	// Inherited via IPopup
	void setupPopUp() override;
	void cleanPopUp() override;
	void onAttach() override;
	void onDetach() override;

private:
	Engine* engine;
};
