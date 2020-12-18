#pragma once
#include "Game/Scenes/Statemachine/SceneStateMachine.h"


/// @brief Pause Pop Up
class AchievementPopup : public Layer
{
public:
	AchievementPopup(EventDispatcher& _dispacther, shared_ptr<SceneStateMachine> _stateMachine);
	~AchievementPopup();

	void setupPopUp(Achievement& achievement);

private:
	EventDispatcher& dispatcher;
	shared_ptr<SceneStateMachine> stateMachine;
};
