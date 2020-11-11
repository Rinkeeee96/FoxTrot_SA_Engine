#pragma once
#include "Game/Levels/Builders/AbstractLevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>

class LevelBuilder : public AbstractLevelBuilder {

#define TILESET_PATH "Assets/Levels/Tilesets/"
#define TILE_IMAGE_PATH "Assets/Levels/Tiles/"

private:

	map<int, string> textureMap;
	map<int, SpriteObject*> spriteMap;

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

	virtual void create() override {
		FileLoader fileLoader;

		// TODO make dynamic from json
		Level* bLevel = new Level(1);

		auto filestream = fileLoader.readFile("C:\\Users\\Max van Nistelrooij\\Documents\\Tiled\\SWA Foxtrot Game\\Maps\\Level 1 - Simple - Large.json");
		nlohmann::json json;
		filestream >> json;
		filestream.close();

		// TODO read from somewhere
		SpriteObject* so0 = new SpriteObject(1, 16, 16, 1, 150, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");
		SpriteObject* so1 = new SpriteObject(100, 37, 50, 1, 150, "Assets/Sprites/Character/adventure.png");
		SpriteObject* so2 = new SpriteObject(101, 37, 50, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png");
		SpriteObject* so3 = new SpriteObject(102, 37, 50, 6, 150, "Assets/Sprites/Character/adventure_run_right.png");
		SpriteObject* so4 = new SpriteObject(103, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_slide.png");
		SpriteObject* so5 = new SpriteObject(104, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png");
		SpriteObject* so8 = new SpriteObject(107, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");
		SpriteObject* so6 = new SpriteObject(105, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png");
		SpriteObject* so7 = new SpriteObject(106, 37, 50, 6, 150, "Assets/Sprites/Character/adventure_run_left.png");
		SpriteObject* so9 = new SpriteObject(108, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png");
		SpriteObject* so10 = new SpriteObject(109, 37, 50, 1, 150, "Assets/Levels/Tiles/slime_blue.png");

		engine.loadSprite(*so0);
		engine.loadSprite(*so1);
		engine.loadSprite(*so2);
		engine.loadSprite(*so3);
		engine.loadSprite(*so4);
		engine.loadSprite(*so5);
		engine.loadSprite(*so6);
		engine.loadSprite(*so7);
		engine.loadSprite(*so8);
		engine.loadSprite(*so9);
		engine.loadSprite(*so10);

		int id = 0;
		int zMin = 0;
		int zMax = 100;
		for (auto& [key, value] : json.items()) {
			// Tiles
			if (key == "tilesets") {
				for (auto& [tileKey, tileValue] : value.items()) {
					int currentGid = tileValue["firstgid"];
					const string& source = tileValue["source"];
					const string& filename = std::filesystem::path(source).filename().string();
					const string& tilesetPath = TILESET_PATH + filename;

					auto tilesetFileStream = fileLoader.readFile(tilesetPath);
					nlohmann::json tilesetJson;
					tilesetFileStream >> tilesetJson;
					tilesetFileStream.close();

					for (auto& [tilesetKey, tilesetValue] : tilesetJson.items()) {
						if (tilesetKey == "tiles") {
							for (auto& [spriteKey, spriteValue] : tilesetValue.items()) {

								const string& spriteSource = spriteValue["image"];
								const string& spriteFilename = std::filesystem::path(spriteSource).filename().string();
								const string& spritePath = TILE_IMAGE_PATH + spriteFilename;

								textureMap.insert(pair<int, string>(currentGid, spritePath));
								currentGid++;
							}
						}
					}
				}
			}
		}

		for (auto& [key, value] : json.items()) {
			// Layers
			if (key == "layers") {
				for (auto& [layerKey, layerValue] : value.items()) 
				{
					if (layerValue["name"] == "Background")
					{
						// TODO
					}
					if (layerValue["name"] == "Properties") {
						// TODO
						for (auto& [objectKey, objectValue] : layerValue["objects"].items())
						{
							for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
							{
								if (objectPropertyValue["name"] == "music") {
									string music = objectPropertyValue["value"];
									map<string, string> sound = {
										{"Leve_Sound", "Assets/Sound/" + music},
									};
									bLevel->setSound(sound);
								}
							}
						}
					}
					if (layerValue["name"] == "Ground") {
						// TODO
						int tileNum = 1;
						int currentX = 0;
						int currentY = 0;
						int tileAmount = layerValue["data"].size();
						for (int tileId : layerValue["data"]) {
							//cout << tileNum << "/" << tileAmount << " (" << ((float)tileNum/(float)tileAmount * 100) << "%)" << endl;
							tileNum++;

							if (tileId != 0) {
								IGround* tile = new BaseGround(id++);

								// TODO get width and height from json
								tile->setWidth(16);
								tile->setHeight(16);
								tile->setStatic(true);
								tile->setPositionX(currentX * 16);
								tile->setPositionY(currentY * 16);

								SpriteObject* tileSprite = nullptr;

								if (spriteMap.find(tileId) == spriteMap.end()) {
									tileSprite = new SpriteObject(tileNum + 300, 16, 16, 1, 300, textureMap[tileId].c_str());
									engine.loadSprite(*tileSprite);
								}
								else {
									tileSprite = spriteMap[tileId];
								}

								tile->registerSprite(SpriteState::DEFAULT, tileSprite);
								tile->changeToState(SpriteState::DEFAULT);

								bLevel->addNewObjectToLayer(1, tile);
							}

							if (currentX == (layerValue["width"] - 1)) {
								currentY++;
								currentX = 0;
								continue;
							}
							currentX++;
						}
					}
					if (layerValue["name"] == "Entities")
					{
						for (auto& [objectKey, objectValue] : layerValue["objects"].items())
						{
							ICharacter* object = nullptr;
							for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
							{
								if (objectPropertyValue["name"] == "type") {
									if (objectPropertyValue["value"] == "player") {
										object = new Player(id++);
										object->registerSprite(SpriteState::DEFAULT, so1);
										object->registerSprite(SpriteState::AIR_ATTACK, so2);
										object->registerSprite(SpriteState::RUN_RIGHT, so3);
										object->registerSprite(SpriteState::SLIDE, so4);
										object->registerSprite(SpriteState::AIR_FALL_LEFT, so5);
										object->registerSprite(SpriteState::AIR_JUMP_LEFT, so6);
										object->registerSprite(SpriteState::AIR_FALL_RIGHT, so8);
										object->registerSprite(SpriteState::AIR_JUMP_RIGHT, so9);
										object->registerSprite(SpriteState::RUN_LEFT, so7);
										object->changeToState(SpriteState::DEFAULT);
									}
									else if (objectPropertyValue["value"] == "slime") {
										object = new Slime(id++);
										object->registerSprite(SpriteState::DEFAULT, so10);
										object->changeToState(SpriteState::DEFAULT);
									}
									else {
										object = new Slime(id++);
										object->registerSprite(SpriteState::DEFAULT, so10);
										object->changeToState(SpriteState::DEFAULT);
										//throw std::exception("invalid type");
									}
								}
							}

							object->setName(objectValue["name"]);
							object->setHeight(objectValue["height"]);
							object->setWidth(objectValue["width"]);
							object->setRotation(objectValue["rotation"]);
							object->setPositionX(objectValue["x"]);
							object->setPositionY(objectValue["y"]);
							object->setStatic(false);



							// TODO sprites

							for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
							{
								if (objectPropertyValue["name"] == "density") {
									int densityString = objectPropertyValue["value"];
									object->setDensity(densityString);
								}
								if (objectPropertyValue["name"] == "friction") {
									int frictionString = objectPropertyValue["value"];
									object->setFriction(frictionString);
								}
								if (objectPropertyValue["name"] == "jump_height") {
									string jump_heightString = objectPropertyValue["value"];
									object->setJumpHeight(stringToFloat(jump_heightString));
								}
								if (objectPropertyValue["name"] == "restitution") {
									int restitutionString = objectPropertyValue["value"];
									object->setRestitution(restitutionString);
								}
								if (objectPropertyValue["name"] == "speed") {
									string speedString = objectPropertyValue["value"];
									object->setSpeed(stringToFloat(speedString));
								}
								if (objectPropertyValue["name"] == "health") {
									string healthString = objectPropertyValue["value"];
									object->setHealth(std::stoi(healthString));
								}
							}
							bLevel->addNewObjectToLayer(3, object);
						}
					}
				}
			}
		}
		
		engine.insertScene(bLevel);
		level = unique_ptr<Level>(bLevel);
	}
};