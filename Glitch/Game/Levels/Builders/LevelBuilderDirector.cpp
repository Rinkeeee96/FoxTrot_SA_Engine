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

				// TODO fix static draw objects
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