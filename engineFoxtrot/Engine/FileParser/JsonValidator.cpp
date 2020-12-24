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
		throw exception("JsonValidator: Failed to load schema document");
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


	valijson::ValidationResults results;
	if (!validator.validate(schema, validateAdapter, &results))
	{
		std::stringstream err_oss;

		valijson::ValidationResults::Error error;
		int error_num = 1;
		while (results.popError(error))
		{
			std::string context;
			std::vector<std::string>::iterator itr = error.context.begin();
			for (; itr != error.context.end(); itr++)
				context += *itr;

			err_oss << "Error #" << error_num << std::endl
				<< "  context: " << context << std::endl
				<< "  desc:    " << error.description << std::endl;
			std::cout << err_oss.str();
			++error_num;
		}
		docIsValid = false;
	}
	else {
		docIsValid = true;
	}
}

/// @brief 
/// returns of the document is valid
/// @return boolean
bool JsonValidator::documentIsValid() {
	return docIsValid;
}