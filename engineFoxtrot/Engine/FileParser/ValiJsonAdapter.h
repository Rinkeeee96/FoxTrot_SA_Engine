#pragma once
#include <fstream> 

#include <rapidjson/document.h>

/// @brief 
/// ValiJson adapter
class API ValiJsonAdapter
{
private:
	void loadJsonDocument(string path, rapidjson::Document& document);
	rapidjson::Document validationDocument;
	rapidjson::Document document; 
public:
	ValiJsonAdapter(string path, string validationPath);
	bool documentIsValid();

	void loadNewDocument(string path);
	void loadNewValidationFile(string path);
};