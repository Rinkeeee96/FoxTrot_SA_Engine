#include "stdafx.h"
#include "ValiJsonAdapter.h"

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>

ValiJsonAdapter::ValiJsonAdapter(string path, string validationPath) {
	loadJsonDocument(path, document);
	loadJsonDocument(validationPath, validationDocument);
}

/// @brief 
/// load a jsonfile to a document
/// @param path to the file
/// @param document reference
void ValiJsonAdapter::loadJsonDocument(string path, rapidjson::Document& document) {
	if (!valijson::utils::loadDocument(path, document)) {
		throw exception("Failed to load schema document");
	}
}

/// @brief 
/// check of the current document is valid by the json schema.
/// @return boolean
bool ValiJsonAdapter::documentIsValid() {
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

/// @brief 
/// validate a json file
/// @param path to the file
void ValiJsonAdapter::loadNewDocument(string path) {
	loadJsonDocument(path, document);
}

/// @brief 
/// validate a new validation file
/// @param path to the file
void ValiJsonAdapter::loadNewValidationFile(string path) {
	loadJsonDocument(path, validationDocument);
}