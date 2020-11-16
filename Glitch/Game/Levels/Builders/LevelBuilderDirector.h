#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>
#include <exception>

class LevelBuilderDirector
{
private:
	map<string, vector<SpriteObject*>> sprites;
	FileLoader fileLoader;
public:
	LevelBuilderDirector(Engine& engine) {
		for (auto spriteMap : sprites) {
			for (auto sprite : spriteMap.second) {
				engine.loadSprite(*sprite);
			}
		}
	}
	void construct(ILevelBuilder* builder);
};

