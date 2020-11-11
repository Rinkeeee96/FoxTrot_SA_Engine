#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>

class LevelBuilderDirector
{
private:
	FileLoader fileLoader;
public:
	// TODO move cpp
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

