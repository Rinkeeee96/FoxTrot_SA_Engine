#pragma once
#include "Game/Levels/Builders/AbstractLevelBuilder.h"

class LevelBuilder : public AbstractLevelBuilder {

#define TILESET_PATH "Assets/Levels/Tilesets/"
#define TILE_IMAGE_PATH "Assets/Levels/Tiles/"

private:
	FileLoader fileLoader;
	map<int, string> textureMap;
	map<int, SpriteObject*> spriteMap;
	Level* bLevel = new Level(1);
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

	float stringToFloat(string stringToParse) {
		try {
			return std::stod(stringToParse);
		}
		catch (int e) {
			throw std::exception("invalid string to float");
		}
	}
public:
	LevelBuilder(Engine& _engine) : AbstractLevelBuilder(_engine) { }

	void createLevel(nlohmann::json json) override;
	void createEntities(nlohmann::json layerValue, int id) override;
	void createBackground(nlohmann::json layerValue, int id) override;
	void createTiles(nlohmann::json layerValue, int id) override;
	void loadTileSets(nlohmann::json json) override;
	void loadSprites() override;
	virtual void create() override;
};