#pragma once
#include <nlohmann\json.hpp>
#include <exception>
#include <string>
#include <Game\Levels\Builders\LevelBuilder.h>
#include <Game\Levels\Builders\LevelBuilderDirector.h>

/// @brief 
/// Facade for coupling load and create functionalities
class LoadLevelFacade
{
public:
	LoadLevelFacade(Engine& _engine) : engine(_engine) { }

	// @brief 
	/// Loads file and constructs using a builder director
	/// @param path 
	/// @param levelbuilder to use 
	void load(string path, ILevelBuilder* levelBuilder) {
		nlohmann::json json;

		try {
			auto filestream = fileLoader.readFile(path);
			filestream >> json;
			filestream.close();

			try {
				builderDirector.construct(json, levelBuilder);
			}
			catch (exception e) {
				cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
				cout << e.what() << "\n";
			}
		}
		catch (exception e) {
			cout << "Something went wrong opening file, make sure the file exists" << "\n";
			cout << e.what() << "\n";
		}
	}
private:
	LevelBuilderDirector builderDirector{ engine };
	Engine& engine;
	FileLoader fileLoader;
};