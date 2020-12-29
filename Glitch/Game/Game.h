#pragma once
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Statemachine/SceneStateMachine.h"
#include "Game/SaveGame/Savegame.h"
#include "Game/AdvertisementHandler/AdvertisementHandler.h"

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	int run();
private:
	unique_ptr<Engine> engine;
	shared_ptr<ICommandBuilder> commandBuilder;
	shared_ptr<Savegame> savegame;

	shared_ptr<SceneStateMachine> stateMachine;

	unique_ptr<AdvertisementHandler> adHandler;

	bool gameRunning = true;
};

