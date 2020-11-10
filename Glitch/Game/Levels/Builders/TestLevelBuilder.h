#pragma once
#include "Game/Levels/Builders/AbstractLevelBuilder.h"

class TestLevelBuilder : public AbstractLevelBuilder {
public:
	TestLevelBuilder(Engine& _engine) : AbstractLevelBuilder(_engine) { }

	virtual void create() override;
};
