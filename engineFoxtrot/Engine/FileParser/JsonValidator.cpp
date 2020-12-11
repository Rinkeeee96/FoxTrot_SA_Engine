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

	JsonDocument document; 
	JsonDocument validationDocument;

	loadDocument(path, document);
	loadDocument(validationPath, validationDocument);
	validate(document, validationDocument);
}

/// @brief 
/// load a jsonfile to a document
/// @param path to the file
/// @param document reference
void JsonValidator::loadDocument(string path, JsonDocument& document) {
	if (!valijson::utils::loadDocument(path, document)) {
		throw exception("Failed to load schema document");
	}
}

/// @brief 
/// check of the document is valid by the validationDocument.
/// @param JsonDocument document
/// @param JsonDocument jsonSchema
/// @return 
void JsonValidator::validate(JsonDocument& document, JsonDocument& validationDocument) {
	valijson::Schema schema;
	valijson::SchemaParser parser;
	valijson::adapters::RapidJsonAdapter schemaAdapter(validationDocument);
	parser.populateSchema(schemaAdapter, schema);

	valijson::Validator validator;
	valijson::adapters::RapidJsonAdapter validateAdapter(document);

	if (!validator.validate(schema, validateAdapter, NULL)) {
		docIsValid = false;
	}

	docIsValid = true;
}

/// @brief 
/// returns of the document is valid
/// @return boolean
bool JsonValidator::documentIsValid() {
	return docIsValid;
}