#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Scenes.h"

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	void run();
	bool stopRun(Event& event);

	void switchToScene(string const identifier, bool useTransitionScreen);

private:
	Engine engine;
	int sceneIdentifierToID(string& identifier);

	shared_ptr<Scene> currentScene;
	bool gameRunning = true;
	int sceneId = 0;
};

