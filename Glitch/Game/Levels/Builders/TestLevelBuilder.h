#pragma once
#include "./LevelBuilder.h"

class TestLevelBuilder : public LevelBuilder {
public:
	TestLevelBuilder(Engine& _engine) : LevelBuilder(_engine) { }

	virtual void create() override;
};
