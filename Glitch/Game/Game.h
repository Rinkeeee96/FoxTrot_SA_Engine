#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"

#define EXIT_SUCCES 0

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	int run();
	bool stopRun(Event& event);


private:
	Engine engine;

	shared_ptr<SceneStateMachine> stateMachine;

	bool gameRunning = true;
};

