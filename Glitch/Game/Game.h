#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "SceneSwitcher/SceneSwitcher.h"
#include "Game/Scenes/MainMenu/MainMenu.h"
#include "Game/Scenes/Transitions/GeneralTransition/GeneralTransition.h"
#include "Game\Scenes\Overworld\Overworld.h"
#include "Game/Scenes/DeathScreen/DeadScreen.h"
#include "Game/Scenes/WinScreen/WinScreen.h"
#include "Game/Scenes/Scenes.h"

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	void run();
	bool stopRun(Event& event);

private:
	Engine engine;
	bool gameRunning = true;
	int sceneId = 0;
};

