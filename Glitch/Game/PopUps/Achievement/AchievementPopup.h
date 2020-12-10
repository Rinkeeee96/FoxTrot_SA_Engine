#pragma once
#include "Game/Scenes/Statemachine/SceneStateMachine.h"


/// @brief Pause Pop Up
class AchievementPopup : public Layer
{
public:
	AchievementPopup(EventDispatcher& _dispacther, SceneStateMachine& _stateMachine);
	~AchievementPopup();

	void setupPopUp(string& achievement);

private:
	EventDispatcher& dispatcher;
	SceneStateMachine& stateMachine;
};
