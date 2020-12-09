#pragma once
#include <fstream> 

/// @brief 
/// Class responsible for opening files
class API FileLoader
{
private:

public:
	ifstream readFile(string path);
	bool validateDocument(string path, string validationPath);
};