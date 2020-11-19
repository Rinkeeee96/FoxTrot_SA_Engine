#include "stdafx.h"
#include "FileLoader.h"

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