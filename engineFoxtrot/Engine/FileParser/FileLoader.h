#pragma once
#include <fstream> 

/// @brief 
/// Class responsible for opening files
class API FileLoader
{
private:
	
public:
	virtual ~FileLoader() {};
	ifstream readFile(const string& path);
	bool validateDocument(const string& path, const string& validationPath);
};