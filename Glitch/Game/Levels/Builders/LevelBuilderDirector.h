#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>

class LevelBuilderDirector
{
private:
	map<string, vector<SpriteObject*>> sprites;
	FileLoader fileLoader;
public:
	LevelBuilderDirector(Engine& engine) {
		// TODO pass to builder for one time register
		sprites["tile"] = { new SpriteObject(1, 16, 16, 1, 150, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png") };
		sprites["enemy"] = { new SpriteObject(109, 37, 50, 1, 150, "Assets/Levels/Tiles/slime_blue.png") };
		sprites["player"] = { 
			new SpriteObject(100, 37, 50, 1, 150, "Assets/Sprites/Character/adventure.png"),
			new SpriteObject(101, 37, 50, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png"),
			new SpriteObject(102, 37, 50, 6, 150, "Assets/Sprites/Character/adventure_run_right.png"),
			new SpriteObject(103, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_slide.png"),
			new SpriteObject(104, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png"),
			new SpriteObject(107, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png"),
			new SpriteObject(105, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png"),
			new SpriteObject(106, 37, 50, 6, 150, "Assets/Sprites/Character/adventure_run_left.png"),
			new SpriteObject(108, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png")
		};

		for (auto spriteMap : sprites) {
			for (auto sprite : spriteMap.second) {
				engine.loadSprite(*sprite);
			}
		}
	}
	// TODO move cpp
	void construct(ILevelBuilder* builder) 
	{
		// TODO Seperate loading from building
		// TODO make dynamic from json
		auto filestream = fileLoader.readFile("C:\\Users\\thijs\\Downloads\\Level 1 - Simple - Large.json");

		nlohmann::json json;
		filestream >> json;
		filestream.close();

		builder->loadSprites();
		builder->loadTileSets(json);
		builder->createLevel(json);

		// TODO Use flatEntity
		for (auto& [key, value] : json.items()) {
			if (key == "layers") {
				for (auto& [layerKey, layerValue] : value.items())
				{
					// TODO Triggers?

					// TODO Fix character not moving

					// TODO fix static draw objects

					// TODO decorations
						// TODO fix physics (oncollision with diffrent layer)
					if (layerValue["name"] == "Background")
					{
						builder->createBackground(layerValue);
					}
					if (layerValue["name"] == "Ground") {
						builder->createTiles(layerValue);
					}
					if (layerValue["name"] == "Decoration") {
						builder->createDecoration(layerValue);
					}
					if (layerValue["name"] == "Particles") {
						builder->createParticle(layerValue);
					}
					if (layerValue["name"] == "Entities")
					{
						builder->createEntities(layerValue);
					}
				}
			}
		}
		builder->create();
	}
};

