#pragma once
#include <fstream> 

#include <rapidjson/document.h>
#include "IFileValidator.h"

using JsonDocument = rapidjson::Document;

/// @brief 
/// ValiJson adapter
class API JsonValidator : public IFileValidator
{
public:
	JsonValidator(string path, string validationPath);

	bool documentIsValid();

private:
	void loadDocument(string path, JsonDocument& document);
	void validate(JsonDocument& document, JsonDocument& validationDocument);
	bool docIsValid = false;
};