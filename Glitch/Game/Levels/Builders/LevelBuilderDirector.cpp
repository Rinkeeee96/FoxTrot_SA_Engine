#include "LevelBuilderDirector.h"

void LevelBuilderDirector::construct(ILevelBuilder* builder) {
	nlohmann::json json;

	try {
		auto filestream = fileLoader.readFile("Assets/Levels/Maps/Level1.json");
		filestream >> json;
		filestream.close();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}

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