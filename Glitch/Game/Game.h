#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Scenes.h"
#include "Game/Scenes/Factory/FactoryMethod.h"

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

	shared_ptr<Scene> currentScene;
	bool gameRunning = true;
	int sceneId = 0;
};

