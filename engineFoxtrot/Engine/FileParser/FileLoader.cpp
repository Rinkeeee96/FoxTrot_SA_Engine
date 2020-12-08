#include "stdafx.h"
#include "FileLoader.h"

#include <FileParser\ValiJsonAdapter.h>
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

/// @brief 
/// validate a json file with a json schema
/// @param path to the file
/// @param path to the validation file
/// @return boolean
bool FileLoader::validateJSON(string path, string validationPath) {
	ValiJsonAdapter valiJsonAdapter(path, validationPath);

	return valiJsonAdapter.documentIsValid();
}