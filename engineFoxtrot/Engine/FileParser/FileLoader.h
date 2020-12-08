#pragma once
#include <fstream> 

/// @brief 
/// Class responsible for opening files
class API FileLoader
{
private:

public:
	ifstream readFile(string path);
	bool validateJSON(string path, string validationPath);
};