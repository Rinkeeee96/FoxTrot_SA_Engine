#pragma once
#include "Game/Levels/Builders/AbstractLevelBuilder.h"
#include <Game\Levels\Builders\Tiles\TileSprite.h>

class LevelBuilder : public AbstractLevelBuilder {

// DO NOT TOUCH
#define GROUND_LAYER_INDEX 2

#define ENTITY_LAYER_INDEX 4
#define DECORATION_LAYER_INDEX 3
#define PARTICLE_LAYER_INDEX 5
#define BACKGROUND_LAYER_INDEX 1

#define TILESET_PATH "Assets/Levels/Tilesets/"
#define TILE_IMAGE_PATH "Assets/Levels/Tiles/"

private:
	FileLoader fileLoader;
	map<int, TileSprite*> textureMap;
	map<int, SpriteObject*> spriteMap;
	// TODO Dynamic
	Level* bLevel = new Level(1);

	// TODO cleanup
	SpriteObject* tileTop = nullptr;
	SpriteObject* playerDefault = nullptr;
	SpriteObject* playerAirAttack = nullptr;
	SpriteObject* playerRunRight = nullptr;
	SpriteObject* playerSlide = nullptr;
	SpriteObject* playerFallLeft = nullptr;
	SpriteObject* playerFallRight = nullptr;
	SpriteObject* playerJumpLeft = nullptr;
	SpriteObject* playerRunLeft = nullptr;
	SpriteObject* playerJumpRight = nullptr;
	SpriteObject* slimeDefault = nullptr;

	// TODO
	int currentTileId = 300;
	int mapTileWidth = 16;
	int mapTileHeight = 16;
	int id = 0;
public:
	LevelBuilder(Engine& _engine) : AbstractLevelBuilder(_engine) { }

	// TODO less json reference
	void createLevel(nlohmann::json json) override;
	void createEntities(nlohmann::json layerValue) override;
	void createBackground(nlohmann::json layerValue) override;
	// TODO Split to function with same functionality with layer as param
	void createDecoration(nlohmann::json layerValue) override;
	void createParticle(nlohmann::json layerValue) override;
	void createTiles(nlohmann::json layerValue) override;
	void loadTileSets(nlohmann::json json) override;
	void loadSprites() override;
	virtual void create() override;
};