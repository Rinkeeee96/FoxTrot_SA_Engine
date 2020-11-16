#include "stdafx.h"
#include "FileLoader.h"

std::ifstream FileLoader::readFile(string path) {
	bool exists = std::filesystem::exists(path);

	if (exists) {
		std::ifstream ifstream(path);
		return ifstream;
	}
	throw std::exception("file not found exception");
}