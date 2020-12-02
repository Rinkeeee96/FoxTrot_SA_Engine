#pragma once
#include "Game\Levels\Builders\AbstractLevelBuilder.h"
#include "Game\Levels\Builders\ParsedEntities\TileSprite.h"
#include "Game\Factories\CharacterFactory.h"
#include "Game\Factories\TriggerFactory.h"
#include "Game\Triggers\DeathTrigger.h"
#include "Game\Triggers\WinTrigger.h"

// DO NOT TOUCH GROUND LAYER INDEX
#define GROUND_LAYER_INDEX 2
#define ENTITY_LAYER_INDEX 4
#define DECORATION_LAYER_INDEX 3
#define PARTICLE_LAYER_INDEX 5
#define BACKGROUND_LAYER_INDEX 1

#define ICHARACTER_HEIGHT 37
#define ICHARACTER_WIDTH 50

#define CHARACTER_PATH "Assets/Sprites/Character/"
#define TILESET_PATH "Assets/Levels/Tilesets/"
#define TILE_IMAGE_PATH "Assets/Levels/Tiles/"

/// @brief 
/// Builder class for creating a level
class LevelBuilder : public AbstractLevelBuilder {
private:
	TriggerFactory triggerFactory;
	std::unique_ptr<CharacterFactory> characterFactory;
	FileLoader fileLoader;
	map<int, TileSprite*> textureMap;
	map<int, SpriteObject*> spriteMap;

	// TODO Fix tileId in tilesets
	Level* bLevel;

	bool getAlwaysDrawFromJson(nlohmann::json layerValue);

	int currentTileId = 999;
	int mapTileWidth = 16;
	int mapTileHeight = 16;
	int textureId = 0;
	int id = 0;
public:
	LevelBuilder(Engine& _engine, int levelId, SceneStateMachine& _statemachine, int _startingTileId = 999);

	void createLevel(nlohmann::json json) override;
	void createEntities(nlohmann::json layerValue) override;
	void createBackground(nlohmann::json layerValue) override;
	void createDecoration(nlohmann::json layerValue) override;
	void createParticle(nlohmann::json layerValue) override;
	void createTiles(nlohmann::json layerValue) override;
	void loadTileSets(nlohmann::json json) override;
	void createTriggers(nlohmann::json json) override;
	void initFactory() override;
	void cleanup() override;

	virtual void create() override;
};