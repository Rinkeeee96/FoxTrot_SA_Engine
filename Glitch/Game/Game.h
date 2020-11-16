#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game\Levels\LoadLevelFacade.h"

class Game
{
public:
	Game();
	void run();
	bool stopRun(Event& event);

private:
	Engine engine;
	bool gameRunning = true;
	int sceneId = 0;
};

