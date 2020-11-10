#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"

class LevelBuilderDirector
{
public:
	void construct(ILevelBuilder* builder) 
	{
		builder->create();
	}
};

