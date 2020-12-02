#pragma once
#include "Game/Levels/Level.h"
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Characters/Enemies/Slime.h"
#include "Game/Characters/Enemies/Fleye.h"
#include "Game/Characters/Enemies/Jumpkin.h"
#include "Game/Ground/BaseGround.h"
#include <nlohmann\json.hpp>

/// @brief 
/// Interface for a levelbuilder
class ILevelBuilder
{
protected:
	std::shared_ptr<Level> level;
public:
	virtual shared_ptr<Level> getLevel() = 0;
	virtual void create() = 0;
	virtual void createLevel(nlohmann::json json) = 0;
	virtual void createEntities(nlohmann::json layerValue) = 0;
	virtual void createTriggers(nlohmann::json json) = 0;
	virtual void createBackground(nlohmann::json layerValue) = 0;
	virtual void createDecoration(nlohmann::json layerValue) = 0;
	virtual void createParticle(nlohmann::json layerValue) = 0;
	virtual void createTiles(nlohmann::json layerValue) = 0;
	virtual void loadTileSets(nlohmann::json json) = 0;
	virtual void initFactory() = 0;
	virtual void cleanup() = 0;
};

