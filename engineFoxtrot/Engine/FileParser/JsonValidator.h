#pragma once
#include <fstream> 

#include <rapidjson/document.h>
#include "IFileValidator.h"

/// @brief 
/// ValiJson adapter
class API JsonValidator : public IFileValidator
{
private:
	void loadDocument(string path, rapidjson::Document& document);
	rapidjson::Document validationDocument;
	rapidjson::Document document; 
public:
	JsonValidator(string path, string validationPath);

	bool documentIsValid();

	void loadNewDocument(string path);
	void loadNewValidationFile(string path);
};