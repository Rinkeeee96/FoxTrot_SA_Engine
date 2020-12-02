#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"
#include "Game/SaveGame/Savegame.h"

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	int run();

private:
	Engine engine;
	Savegame savegame;

	SceneStateMachine stateMachine{ engine,savegame };

	bool gameRunning = true;
};

