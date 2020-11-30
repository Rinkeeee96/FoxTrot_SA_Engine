#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"

/// @brief 
/// Abstract builder class for creating a level
class AbstractLevelBuilder : public ILevelBuilder {
protected:
	Engine& engine;
public:
	AbstractLevelBuilder(Engine& _engine) : engine(_engine) { }

	shared_ptr<Level> getLevel() override { return level; }

	virtual void create() = 0;
	virtual void createLevel(nlohmann::json json) = 0;
	virtual void createEntities(nlohmann::json layerValue) = 0;
	virtual void createTriggers(nlohmann::json json) = 0;
	virtual void createBackground(nlohmann::json layerValue) = 0;
	virtual void createTiles(nlohmann::json layerValue) = 0;
	virtual void loadTileSets(nlohmann::json json) = 0;
	virtual void initFactory() = 0;
};