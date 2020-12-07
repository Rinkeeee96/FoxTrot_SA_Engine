#include "pch.h"
#include "LoadLevelFacade.h"

#include <rapidjson/document.h>

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>

using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::adapters::RapidJsonAdapter;

LoadLevelFacade::LoadLevelFacade(Engine& _engine) : engine(_engine) 
{ 
}


// @brief 
/// Validates the level file
/// @param path 
void LoadLevelFacade::validateLevel(string path) {
	// Load JSON document using RapidJSON with Valijson helper function
	rapidjson::Document mySchemaDoc;
	if (!valijson::utils::loadDocument("Game/Levels/level-validation-schema.json", mySchemaDoc)) {
		throw exception("Failed to load schema document");
	}

	// Parse JSON schema content using valijson
	Schema mySchema;
	SchemaParser parser;
	RapidJsonAdapter mySchemaAdapter(mySchemaDoc);
	parser.populateSchema(mySchemaAdapter, mySchema);

	rapidjson::Document myTargetDoc;
	if (!valijson::utils::loadDocument(path, myTargetDoc)) {
		throw exception("Failed to load target document");
	}

	Validator validator;
	RapidJsonAdapter myTargetAdapter(myTargetDoc);
	if (!validator.validate(mySchema, myTargetAdapter, NULL)) {
		throw exception("Validation failed.");
	}
}

// @brief 
/// Loads file and constructs using a builder director
/// @param path 
/// @param levelbuilder to use 
void LoadLevelFacade::load(string path, ILevelBuilder* levelBuilder) {
	try {
		validateLevel(path);

		nlohmann::json json;
		builderDirector = LevelBuilderDirector();
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
	catch (exception exc) {
		cout << "Something went wrong validating file, make sure the file is correct" << "\n";
		cout << exc.what() << "\n";
		throw exc;
	}
}