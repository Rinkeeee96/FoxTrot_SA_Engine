#pragma once
#include "../Level.h"
#include "../../SpriteState.h"
#include "../../Player/Player.h"

class ILevelBuilder
{
protected:
	std::unique_ptr<Level> level;
public:
	virtual Level* getLevel() = 0;
	virtual void create() = 0;
};

