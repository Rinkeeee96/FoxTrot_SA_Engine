#pragma once
#include <nlohmann\json.hpp>
#include "Game\Levels\Builders\LevelBuilder.h"
#include "Game\Levels\Builders\LevelBuilderDirector.h"

/// @brief 
/// Facade for coupling load and create functionalities
class LoadLevelFacade
{
public:
	LoadLevelFacade(unique_ptr<Engine>& _engine);

	void load(string path, ILevelBuilder* levelBuilder);
private:
	LevelBuilderDirector builderDirector;
	unique_ptr<Engine>& engine;
	FileLoader fileLoader;
};