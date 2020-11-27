#pragma once
#include <nlohmann\json.hpp>
#include "Game\Levels\Builders\LevelBuilder.h"
#include "Game\Levels\Builders\LevelBuilderDirector.h"

#include <rapidjson/document.h>

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>

/// @brief 
/// Facade for coupling load and create functionalities
class LoadLevelFacade
{
public:
	LoadLevelFacade(Engine& _engine);

	void load(string path, ILevelBuilder* levelBuilder);
private:
	LevelBuilderDirector builderDirector;
	Engine& engine;
	FileLoader fileLoader;
};