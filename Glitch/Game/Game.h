#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"

#define EXIT_SUCCES 0
#define EXIT_FAILURE -1

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

