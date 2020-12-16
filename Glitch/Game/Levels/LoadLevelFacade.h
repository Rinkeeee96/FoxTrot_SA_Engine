#pragma once
#include <nlohmann\json.hpp>
#include "Game\Levels\Builders\LevelBuilder.h"
#include "Game\Levels\Builders\LevelBuilderDirector.h"

/// @brief 
/// Facade for coupling load and create functionalities
class LoadLevelFacade
{
public:
	LoadLevelFacade();

	void load(string path, ILevelBuilder* levelBuilder);
private:
	LevelBuilderDirector builderDirector;
	FileLoader fileLoader;
};