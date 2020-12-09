#pragma once
#include <fstream> 

#include <rapidjson/document.h>
#include "IFileValidator.h"

using JsonDocument = rapidjson::Document;

/// @brief 
/// ValiJson adapter
class API JsonValidator : public IFileValidator
{
private:
	void loadDocument(string path, JsonDocument& document);
	JsonDocument validationDocument;
	JsonDocument document;
public:
	JsonValidator(string path, string validationPath);

	bool documentIsValid();

	void loadNewDocument(string path);
	void loadNewValidationFile(string path);
};