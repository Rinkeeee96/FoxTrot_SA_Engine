#include "pch.h"
#include "LoadLevelFacade.h"

LoadLevelFacade::LoadLevelFacade(unique_ptr<Engine>& _engine) : engine(_engine)
{ 
}


// @brief 
/// Loads file and constructs using a builder director
/// @param path 
/// @param levelbuilder to use 
void LoadLevelFacade::load(string path, ILevelBuilder* levelBuilder) {
	FileLoader fileLoader;
	nlohmann::json json;
	builderDirector = LevelBuilderDirector();
	try {
		auto filestream = fileLoader.readFile(path);
		filestream >> json;
		filestream.close();

		bool validLevel = true;// fileLoader.validateDocument(path, "Assets/Levels/Maps/level-validation-schema.json");

		if (validLevel){
			try {
				builderDirector.construct(json, levelBuilder);
			}
			catch (exception exc) {
				cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
				cout << exc.what() << "\n";
				throw exc;
			}
		}
		else{
			throw exception("LoadLevelFacade: Something went wrong validating file, make sure the file is correct");
		}
	}
	catch (exception exc) {
		cout << "Something went wrong opening file, make sure the file exists" << "\n";
		cout << exc.what() << "\n";
		throw exc;
	}
}