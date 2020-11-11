#pragma once
#include "Game/Levels/Level.h"
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Levels/Builders/ILevelBuilder.h"
#include "Levels/Builders/LevelBuilderDirector.h"
#include "Levels/Builders/LevelBuilder.h"

class Game
{
public:
	void run();

private:
	Engine engine;
	bool gameRunning = true;
};

