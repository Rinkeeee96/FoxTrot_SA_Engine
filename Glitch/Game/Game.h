#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "SceneSwitcher/SceneSwitcher.h"
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

	unique_ptr<Scene> currentScene;
	bool gameRunning = true;
	int sceneId = 0;
};

