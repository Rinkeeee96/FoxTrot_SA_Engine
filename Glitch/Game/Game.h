#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game\Levels\LoadLevelFacade.h"

class Game
{
public:
	void run();

private:
	Engine engine;
	bool gameRunning = true;
};

