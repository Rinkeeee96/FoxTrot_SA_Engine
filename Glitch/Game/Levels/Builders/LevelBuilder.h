#pragma once
#include "Game/Levels/Builders/AbstractLevelBuilder.h"
#include <Game\Levels\Builders\Tiles\TileSprite.h>

class LevelBuilder : public AbstractLevelBuilder {

#define GROUND_LAYER_INDEX 1
#define ENTITY_LAYER_INDEX 2
#define DECORATION_LAYER_INDEX 3
#define BACKGROUND_LAYER_INDEX 4

#define TILESET_PATH "Assets/Levels/Tilesets/"
#define TILE_IMAGE_PATH "Assets/Levels/Tiles/"

private:
	FileLoader fileLoader;
	map<int, TileSprite*> textureMap;
	map<int, SpriteObject*> spriteMap;
	// TODO Dynamic
	Level* bLevel = new Level(1);

	// TODO cleanup
	SpriteObject* tileTop;
	SpriteObject* playerDefault;
	SpriteObject* playerAirAttack;
	SpriteObject* playerRunRight;
	SpriteObject* playerSlide;
	SpriteObject* playerFallLeft;
	SpriteObject* playerFallRight;
	SpriteObject* playerJumpLeft;
	SpriteObject* playerRunLeft;
	SpriteObject* playerJumpRight;
	SpriteObject* slimeDefault;

	// TODO
	int currentTileId = 300;
	int mapTileWidth = 16;
	int mapTileHeight = 16;

	// TODO remove?
	float stringToFloat(string stringToParse) {
		try {
			return std::stod(stringToParse);
		}
		catch (int e) {
			throw std::exception("invalid string to float");
		}
	}
public:
	// TODO fix warning
	LevelBuilder(Engine& _engine) : AbstractLevelBuilder(_engine) { }

	// TODO less json reference
	void createLevel(nlohmann::json json) override;
	void createEntities(nlohmann::json layerValue, int id) override;
	void createBackground(nlohmann::json layerValue, int id) override;
	// TODO Split to function with same functionality with layer as param
	void createDecoration(nlohmann::json layerValue, int id) override;
	void createTiles(nlohmann::json layerValue, int id) override;
	void loadTileSets(nlohmann::json json) override;
	void loadSprites() override;
	virtual void create() override;
};