#include "stdafx.h"
#include "FileLoader.h"


#include <rapidjson/document.h>

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>

/// @brief 
/// Reads a file and returns the stream, strem should be closed
/// @param path to the file
/// @throws file not found exception
ifstream FileLoader::readFile(string path) {
	bool exists = filesystem::exists(path);

	if (exists) {
		ifstream ifstream(path);
		return ifstream;
	}
	throw exception("file not found exception");
}
/*
void FileLoader::loadJsonDocument(string path, rapidjson::Document& document) {
	if (!valijson::utils::loadDocument(path, document)) {
		throw exception("Failed to load schema document");
	}
}*/

bool FileLoader::validateJSON(string path, string validationPath) {
	rapidjson::Document validationDocument;
	//loadJsonDocument(validationPath, validationDocument);
	if (!valijson::utils::loadDocument(validationPath, validationDocument)) {
		throw exception("Failed to load schema document");
	}

	rapidjson::Document document;
	//loadJsonDocument(path, document); 
	if (!valijson::utils::loadDocument(path, document)) {
		throw exception("Failed to load schema document");
	}

	// Parse JSON schema content using valijson
	valijson::Schema schema;
	valijson::SchemaParser parser;
	valijson::adapters::RapidJsonAdapter schemaAdapter(validationDocument);
	parser.populateSchema(schemaAdapter, schema);

	valijson::Validator validator;
	valijson::adapters::RapidJsonAdapter validateAdapter(document);

	if (!validator.validate(schema, validateAdapter, NULL)) {
		return false;
	}

	return true;
}