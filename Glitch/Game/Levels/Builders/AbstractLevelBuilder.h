#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"

class AbstractLevelBuilder : public ILevelBuilder {
protected:
	Engine& engine;
public:
	AbstractLevelBuilder(Engine& _engine) : engine(_engine) { }

	Level* getLevel() override { return level.get(); }

	virtual void create() = 0;
	virtual void createLevel(nlohmann::json json) = 0;
	virtual void createEntities(nlohmann::json layerValue) = 0;
	virtual void createBackground(nlohmann::json layerValue) = 0;
	virtual void createTiles(nlohmann::json layerValue) = 0;
	virtual void loadTileSets(nlohmann::json json) = 0;
	virtual void initFactory() = 0;
};