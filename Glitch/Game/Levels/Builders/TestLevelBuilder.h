#pragma once
#include "./AbstractLevelBuilder.h"

class TestLevelBuilder : public AbstractLevelBuilder {
public:
	TestLevelBuilder(Engine& _engine) : AbstractLevelBuilder(_engine) { }

	virtual void create() override;
};
