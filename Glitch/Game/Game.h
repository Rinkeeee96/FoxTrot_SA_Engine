#pragma once
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	int run();

private:
	Engine engine;
	SceneStateMachine stateMachine{ engine };

	bool gameRunning = true;
};

