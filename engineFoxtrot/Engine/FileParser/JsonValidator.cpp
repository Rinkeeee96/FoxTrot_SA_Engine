#include "stdafx.h"
#include "JsonValidator.h"

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>

/// @brief
/// load the documents for validation
/// @param path to document that needs a validation
/// @param path to document that is the validation schema
JsonValidator::JsonValidator(string path, string validationPath) : IFileValidator(path, validationPath) {
	loadDocument(path, document);
	loadDocument(validationPath, validationDocument);
}

/// @brief 
/// load a jsonfile to a document
/// @param path to the file
/// @param document reference
void JsonValidator::loadDocument(string path, rapidjson::Document& document) {
	if (!valijson::utils::loadDocument(path, document)) {
		throw exception("Failed to load schema document");
	}
}

/// @brief 
/// check of the current document is valid by the json schema.
/// @return boolean
bool JsonValidator::documentIsValid() {
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
void JsonValidator::loadNewDocument(string path) {
	loadDocument(path, document);
}

/// @brief 
/// validate a new validation file
/// @param path to the file
void JsonValidator::loadNewValidationFile(string path) {
	loadDocument(path, validationDocument);
}