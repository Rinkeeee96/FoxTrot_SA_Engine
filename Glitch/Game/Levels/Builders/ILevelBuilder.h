#pragma once
#include "Game/Levels/Level.h"
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Characters/Enemies/Slime.h"
#include "Game/Ground/BaseGround.h"

class ILevelBuilder
{
protected:
	std::unique_ptr<Level> level;
public:
	virtual Level* getLevel() = 0;
	virtual void create() = 0;
};

