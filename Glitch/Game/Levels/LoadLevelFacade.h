#pragma once
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>
#include <exception>
#include <string>
#include <Game\Levels\Builders\LevelBuilder.h>
#include <Game\Levels\Builders\LevelBuilderDirector.h>

class LoadLevelFacade
{
public:
	LoadLevelFacade(Engine& _engine) : engine(_engine) { }

	void load(std::string path, ILevelBuilder* levelBuilder) {
		nlohmann::json json;

		try {
			auto filestream = fileLoader.readFile(path);
			filestream >> json;
			filestream.close();

			try {
				builderDirector.construct(json, levelBuilder);
			}
			catch (std::exception e) {
				std::cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
				std::cout << e.what() << "\n";
			}
		}
		catch (std::exception e) {
			std::cout << "Something went wrong opening file, make sure the file exists" << "\n";
			std::cout << e.what() << "\n";
		}
	}
private:
	LevelBuilderDirector builderDirector{ engine };
	Engine& engine;
	FileLoader fileLoader;
};