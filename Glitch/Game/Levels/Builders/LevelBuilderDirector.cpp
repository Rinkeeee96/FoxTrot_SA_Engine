#include "pch.h"
#include "LevelBuilderDirector.h"

LevelBuilderDirector::LevelBuilderDirector(Engine& engine) {
}

void LevelBuilderDirector::construct(nlohmann::json json, ILevelBuilder* builder) {
	builder->loadTileSets(json);
	builder->createLevel(json);

	for (auto& [key, value] : json.items()) {
		if (key == "layers") {
			for (auto& [layerKey, layerValue] : value.items())
			{
				// TODO Triggers?
				if (layerValue["name"] == "Triggers") {
					builder->createTriggers(layerValue);
				}
				// TODO fix static draw objects
				else if (layerValue["name"] == "Background")
				{
					builder->createBackground(layerValue);
				}
				else if (layerValue["name"] == "Ground") {
					builder->createTiles(layerValue);
				}
				else if (layerValue["name"] == "Decoration") {
					builder->createDecoration(layerValue);
				}
				else if (layerValue["name"] == "Particles") {
					builder->createParticle(layerValue);
				}
				else if (layerValue["name"] == "Entities")
				{
					builder->createEntities(layerValue);
				}
			}
		}
	}
	builder->create();
}