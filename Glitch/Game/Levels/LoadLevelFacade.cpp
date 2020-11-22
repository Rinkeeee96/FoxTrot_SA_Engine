#include "pch.h"
#include "LoadLevelFacade.h"

LoadLevelFacade::LoadLevelFacade(Engine& _engine) : engine(_engine) 
{ 
}

// @brief 
/// Loads file and constructs using a builder director
/// @param path 
/// @param levelbuilder to use 
void LoadLevelFacade::load(string path, ILevelBuilder* levelBuilder) {
	nlohmann::json json;

	try {
		auto filestream = fileLoader.readFile(path);
		filestream >> json;
		filestream.close();

		try {
			builderDirector.construct(json, levelBuilder);
		}
		catch (exception exc) {
			cout << "Something went wrong parsing the file, make sure the file is correctly structured" << "\n";
			cout << exc.what() << "\n";
			throw exc;
		}
	}
	catch (exception exc) {
		cout << "Something went wrong opening file, make sure the file exists" << "\n";
		cout << exc.what() << "\n";
		throw exc;
	}
}