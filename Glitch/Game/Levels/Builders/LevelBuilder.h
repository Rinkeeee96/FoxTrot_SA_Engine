#pragma once
#include "Game/Levels/Builders/AbstractLevelBuilder.h"
#include <Game\Levels\Builders\ParsedEntities\TileSprite.h>
#include <Game\Factories\CharacterFactory.h>

class LevelBuilder : public AbstractLevelBuilder {

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

private:
	CharacterFactory characterFactory;
	FileLoader fileLoader;
	map<int, TileSprite*> textureMap;
	map<int, SpriteObject*> spriteMap;
	// TODO Dynamic
	Level* bLevel = new Level(1);

	int currentTileId = 300;
	int mapTileWidth = 16;
	int mapTileHeight = 16;
	int textureId = 0;
	int id = 0;
public:
	LevelBuilder(Engine& _engine);

	// TODO less json reference
	void createLevel(nlohmann::json json) override;
	void createEntities(nlohmann::json layerValue) override;
	void createBackground(nlohmann::json layerValue) override;
	// TODO Split to function with same functionality with layer as param
	void createDecoration(nlohmann::json layerValue) override;
	void createParticle(nlohmann::json layerValue) override;
	void createTiles(nlohmann::json layerValue) override;
	void loadTileSets(nlohmann::json json) override;
	void initFactory() override;
	virtual void create() override;
};