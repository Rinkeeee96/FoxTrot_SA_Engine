#pragma once
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
	unique_ptr<Engine> engine;
	ICommandBuilder* commandBuilder;
	shared_ptr<Savegame> savegame;

	shared_ptr<SceneStateMachine> stateMachine;

	bool gameRunning = true;
};

