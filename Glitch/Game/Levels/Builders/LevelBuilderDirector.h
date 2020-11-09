#pragma once
#include "./ILevelBuilder.h"

class LevelBuilderDirector
{
public:
	void construct(ILevelBuilder* builder) 
	{
		builder->create();
	}
};

