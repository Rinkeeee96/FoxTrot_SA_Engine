#pragma once
#include "./ILevelBuilder.h"

class AbstractLevelBuilder : public ILevelBuilder {
protected:
	Engine& engine;
public:
	AbstractLevelBuilder(Engine& _engine) : engine(_engine) { }

	Level* getLevel() override { return level.get(); }
	virtual void create() = 0;
};