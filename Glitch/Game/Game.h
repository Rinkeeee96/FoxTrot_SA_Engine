#pragma once
#include "./Levels/Level.h"
#include "./SpriteState.h"
#include "./Player/Player.h"

class Game
{
public:
	void run();

private:
	Engine engine;
	bool gameRunning = true;
};

