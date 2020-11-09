#pragma once
#include "./ILevelBuilder.h"

class LevelBuilder : public ILevelBuilder {
protected:
	Engine& engine;
public:
	LevelBuilder(Engine& _engine) : engine(_engine) { }

	Level* getLevel() override { return level.get(); }
	virtual void create() = 0;
};