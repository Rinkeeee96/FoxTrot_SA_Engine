#include "pch.h"
#include "LevelBuilderDirector.h"

LevelBuilderDirector::LevelBuilderDirector() 
{ 
}

// @brief 
/// Construcs a level using a jsonFile and the builder that should be used
/// @param json 
/// @param ILevelBuilder 
void LevelBuilderDirector::construct(nlohmann::json json, ILevelBuilder* builder) {
	builder->loadTileSets(json);
	builder->createLevel(json);

	for (auto& [key, value] : json.items()) {
		if (key == "layers") {
			for (auto& [layerKey, layerValue] : value.items())
			{
				if (layerValue["name"] == "Triggers") {
					builder->createTriggers(layerValue);
				}
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
					//builder->createParticle(layerValue);
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