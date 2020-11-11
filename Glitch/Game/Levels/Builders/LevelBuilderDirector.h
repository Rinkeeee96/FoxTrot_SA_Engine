#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>

class LevelBuilderDirector
{
private:
	FileLoader fileLoader;
public:
	void construct(ILevelBuilder* builder) 
	{
		// TODO make dynamic from json
		auto filestream = fileLoader.readFile("C:\\Users\\thijs\\Downloads\\Level 1 - Simple - Large.json");

		nlohmann::json json;
		filestream >> json;
		filestream.close();

		builder->loadSprites();
		builder->loadTileSets(json);
		builder->createLevel(json);

		int id = 0;
		for (auto& [key, value] : json.items()) {
			if (key == "layers") {
				for (auto& [layerKey, layerValue] : value.items())
				{
					if (layerValue["name"] == "Background")
					{
						builder->createBackground(layerValue, id);
					}
					if (layerValue["name"] == "Ground") {
						builder->createTiles(layerValue, id);
					}
					if (layerValue["name"] == "Entities")
					{
						builder->createEntities(layerValue, id);
					}
				}
			}
		}
		builder->create();
	}
};

