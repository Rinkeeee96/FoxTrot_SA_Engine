#pragma once
#include <fstream> 

/// @brief 
/// Class responsible for opening files
class API FileLoader
{
private:
	virtual ~FileLoader() {};
public:
	ifstream readFile(string path);
	bool validateDocument(string path, string validationPath);
};