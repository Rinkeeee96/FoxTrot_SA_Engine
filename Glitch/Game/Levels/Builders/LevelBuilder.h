#pragma once
#include "./AbstractLevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>

class LevelBuilder : public AbstractLevelBuilder {
private:
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
		map<string, string> soundL1 = {
			{"Level_1_Sound", "Assets/Sound/file_example_WAV_1MG.wav"},
		};
		Level* bLevel = new Level(1, soundL1);

		auto filestream = fileLoader.readFile("C:\\Users\\thijs\\Downloads\\Level 1 - Simple.json");
		nlohmann::json json;
		filestream >> json;
		filestream.close();

		// TODO read from somewhre
		SpriteObject* so0 = new SpriteObject(1, 16, 16, 1, 300, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");
		SpriteObject* so1 = new SpriteObject(100, 37, 50, 1, 300, "Assets/Sprites/Character/adventure.png");
		SpriteObject* so2 = new SpriteObject(101, 37, 50, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png");
		SpriteObject* so3 = new SpriteObject(102, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
		SpriteObject* so4 = new SpriteObject(103, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_slide.png");
		SpriteObject* so5 = new SpriteObject(104, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png");
		SpriteObject* so8 = new SpriteObject(107, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");
		SpriteObject* so6 = new SpriteObject(105, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png");
		SpriteObject* so7 = new SpriteObject(106, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_left.png");
		SpriteObject* so9 = new SpriteObject(108, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png");
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

		int id = 0;

		for (auto& [key, value] : json.items()) {
			if (key == "layers") {
				for (auto& [layerKey, layerValue] : value.items()) 
				{
					for (auto& [objectKey, objectValue] : layerValue["objects"].items())
					{
						// TODO player or enemy?
						Object* object = new Object(1);
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
								object->setDensity(stringToFloat(objectPropertyKey));
							}
							if (objectPropertyValue["name"] == "friction") {
								object->setFriction(stringToFloat(objectPropertyKey));
							}
							if (objectPropertyValue["name"] == "jump_height") {
								object->setJumpHeight(stringToFloat(objectPropertyKey));
							}
							if (objectPropertyValue["name"] == "restitution") {
								object->setRestitution(stringToFloat(objectPropertyKey));
							}
							if (objectPropertyValue["name"] == "speed") {
								object->setSpeed(stringToFloat(objectPropertyKey));
							}
							// TODO Health
							if (objectPropertyValue["name"] == "health") {
							}
						}
					}
				}
			}
		// Tiles
			if (key == "tilesets") {
				Object* tile = new Object(id++);
				tile->setScalable(true);
				tile->setWidth(json["tilewidth"]);
				tile->setHeight(json["tileheight"]);
				// TODO position
				tile->setPositionX(20); 
				tile->setPositionY(300);
				tile->setStatic(true);
				// TODO sprite
				tile->registerSprite(SpriteState::DEFAULT, so0);
				tile->changeToState(SpriteState::DEFAULT);
				bLevel->addNewObjectToLayer(1, tile);
			}
		}
		
		engine.insertScene(bLevel);
		level = unique_ptr<Level>(bLevel);
	}
};


