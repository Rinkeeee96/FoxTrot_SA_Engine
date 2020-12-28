#include "stdafx.h"
#include "FileLoader.h"
#include <FileParser\JsonValidator.h>

/// @brief 
/// Reads a file and returns the stream, strem should be closed
/// @param path to the file
/// @throws file not found exception
ifstream FileLoader::readFile(const string& path) {
	filesystem::path path_{ path };
	bool exists = filesystem::exists(path_);

	if (exists) {
		ifstream ifstream(path);
		return ifstream;
	}

	throw exception("FileLoader: file not found exception");
}

/// @brief 
/// validate a json file with a json schema
/// @param path to the file
/// @param path to the validation file
/// @return boolean
bool FileLoader::validateDocument(string path, string validationPath) {
	auto fileType = path.substr(path.find_last_of(".") + 1);

	if (fileType == "json") {
		JsonValidator valiJsonAdapter(path, validationPath);
		return valiJsonAdapter.documentIsValid();
	}else{
		throw exception("FileLoader: unsupported file type");
	}
	return false;
}