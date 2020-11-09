#pragma once
#include "./LevelBuilder.h"

class LevelOneBuilder : public LevelBuilder {
public:
	LevelOneBuilder(Engine& _engine) : LevelBuilder(_engine) { }

	virtual void create() override {
		FileParser p;

		p.readJSON("C:\\Users\\thijs\\Downloads\\Level 1 - Simple.json");
	}
};


