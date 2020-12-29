#include "stdafx.h"
#include "FileLoader.h"
#include <FileParser\JsonValidator.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstdint>
namespace fs = std::filesystem;

#include<Windows.h>

#include <tchar.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")


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

bool FileLoader::doesFileExist(const string& path)
{
	return fs::exists(path);
}

///  @brief
/// Downloads a file from the web and saves it to the given filepath
void FileLoader::downloadFile(const string& url, const string& pathAndFilename)
{
	HRESULT hr;
	const char* t = url.c_str();
	const char* p = pathAndFilename.c_str();
	hr = URLDownloadToFileA(0, t, p, 0, 0);
}
