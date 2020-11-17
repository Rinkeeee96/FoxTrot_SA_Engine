#pragma once
#include "Game/Levels/Builders/ILevelBuilder.h"
#include <nlohmann\json.hpp>

/// @brief 
/// Builder director, creates a level using a builder
class LevelBuilderDirector
{
private:
	FileLoader fileLoader;
public:
	LevelBuilderDirector(Engine& engine);
	void construct(nlohmann::json json, ILevelBuilder* builder);
};

